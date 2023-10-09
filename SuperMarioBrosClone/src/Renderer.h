#pragma once

#include "Shader.h"
#include "Camera.h"

class Renderer {
private:
	static constexpr unsigned int MAX_QUADS = 100;
	static constexpr unsigned int MAX_VERTICES = MAX_QUADS * 4;
	static constexpr unsigned int MAX_INDICES = MAX_QUADS * 6;

	static struct RenderData {
		unsigned int vao;
		unsigned int vbo;
		unsigned int ibo;

		unsigned int bVao;
		unsigned int bVbo;
		unsigned int bIbo;

		Shader* shader;
	};

	static struct Vertex {
		const glm::vec2 position;
		const glm::vec4 color;

		Vertex() : position(0.0f), color(0.0f) {}
		Vertex(const glm::vec2& position, const glm::vec4& color): position(position), color(color) {}
	};

	static RenderData m_RenderData;
	static std::vector<Vertex> m_BatchedVertices;
	static bool m_Batching;

public:
	static void Init();
	static void Destroy();

	static void BeginCamera(Camera* camera);
	static void BeginBatch();
	static void EndBatch();
	static void DrawQuad(const glm::vec2& position, const float& rotation, const float& scale, const glm::vec4& color);
};