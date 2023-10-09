#include <glad/glad.h>
#include <array>
#include <iostream>

#include "Renderer.h"

Renderer::RenderData Renderer::m_RenderData;
std::vector<Renderer::Vertex> Renderer::m_BatchedVertices;
bool Renderer::m_Batching = false;

void Renderer::Init() {
	//m_BatchedVertices.resize(MAX_VERTICES);
	m_RenderData.shader = &Shader::Get("Flat");

	std::array<Vertex, 4> vertices = {
		Vertex(glm::vec2(-0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec2( 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec2( 0.5f,  0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec2(-0.5f,  0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
	};

	std::array<unsigned int, 6> indices = {
		0, 1, 2,
		2, 3, 0
	};

	std::array<unsigned int, MAX_INDICES> bIndices = {};
	for (size_t i = 0; i < MAX_QUADS; ++i) {
		size_t offset = i * 4;
		size_t index = i * 6;

		bIndices[index]		= 0 + offset;
		bIndices[index + 1] = 1 + offset;
		bIndices[index + 2] = 2 + offset;
		bIndices[index + 3] = 2 + offset;
		bIndices[index + 4] = 3 + offset;
		bIndices[index + 5] = 0 + offset;
	}

	glGenVertexArrays(1, &m_RenderData.vao);
	glBindVertexArray(m_RenderData.vao);

	glGenBuffers(1, &m_RenderData.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderData.vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_RenderData.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderData.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(m_RenderData.vao, 0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexArrayAttrib(m_RenderData.vao, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glGenVertexArrays(1, &m_RenderData.bVao);
	glBindVertexArray(m_RenderData.bVao);

	glGenBuffers(1, &m_RenderData.bVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderData.bVbo);
	glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &m_RenderData.bIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderData.bIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bIndices.size() * sizeof(float), bIndices.data(), GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(m_RenderData.bVao, 0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexArrayAttrib(m_RenderData.bVao, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
}

void Renderer::Destroy() {
	glDeleteBuffers(1, &m_RenderData.bVbo);
	glDeleteBuffers(1, &m_RenderData.bIbo);
	glDeleteVertexArrays(1, &m_RenderData.bVao);

	glDeleteBuffers(1, &m_RenderData.vbo);
	glDeleteBuffers(1, &m_RenderData.ibo);
	glDeleteVertexArrays(1, &m_RenderData.vao);
}

void Renderer::BeginCamera(Camera* camera) {
	m_RenderData.shader->Bind();
	m_RenderData.shader->SetMatrix4("u_Projection", camera->GetProjection());
	m_RenderData.shader->SetMatrix4("u_View", camera->GetView());
}

void Renderer::DrawQuad(const glm::vec2& position, const float& rotation, const float& scale, const glm::vec4& color) {
	if (m_Batching) {
		const auto& newPosition = glm::vec2(position.x - scale / 2.0f, position.y - scale / 2.0f);
		m_BatchedVertices.emplace_back(glm::vec2(newPosition.x, newPosition.y), color);
		m_BatchedVertices.emplace_back(glm::vec2(newPosition.x + scale, newPosition.y), color);
		m_BatchedVertices.emplace_back(glm::vec2(newPosition.x + scale, newPosition.y + scale), color);
		m_BatchedVertices.emplace_back(glm::vec2(newPosition.x, newPosition.y + scale), color);

		return;
	}

	m_RenderData.shader->Bind();
	m_RenderData.shader->SetBool("u_Batch", false);
	m_RenderData.shader->SetVector4("u_Color", color);
	m_RenderData.shader->SetMatrix4(
		"u_Model",
		glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f }) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
		glm::scale(glm::mat4(1.0f), { scale, scale, 0.0f })
	);

	glBindVertexArray(m_RenderData.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	m_RenderData.shader->UnBind();
	glBindVertexArray(0);
}

void Renderer::BeginBatch() {
	m_Batching = true;
}

void Renderer::EndBatch() {
	m_RenderData.shader->Bind();
	m_RenderData.shader->SetBool("u_Batch", true);
	m_RenderData.shader->SetMatrix4("u_Model", glm::mat4(1.0f));

	glBindVertexArray(m_RenderData.bVao);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_BatchedVertices.size() * sizeof(Vertex), m_BatchedVertices.data());
	glDrawElements(GL_TRIANGLES, MAX_INDICES, GL_UNSIGNED_INT, nullptr);

	m_RenderData.shader->UnBind();
	glBindVertexArray(0);

	m_BatchedVertices.clear();
	m_Batching = false;
}