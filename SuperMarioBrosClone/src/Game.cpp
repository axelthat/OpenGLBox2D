#include <iostream>

#include "imgui/imgui.h"
#include "Game.h"
#include "Time.h"
#include "Shader.h"
#include "Renderer.h"
#include "Camera.h"
#include "Wall.h"
#include "Util.h"

Game::Game(unsigned int width, unsigned int height):
	character(nullptr)
{
	LoadShaders();

	Renderer::Init();

	m_PhysicsWorld = new b2World({ 0.0f, -9.81f });

	character = new Character(*m_PhysicsWorld);
	camera = new Camera(width, height);

	for (size_t i = 0; i < 100; ++i) {
		auto x = static_cast<float>(Util::GetRandomNumber<int>(0, width));
		auto y = static_cast<float>(Util::GetRandomNumber<int>(0, height));

		gameObjects.push_back(std::make_unique<Wall>(glm::vec2(50.0f * i + i * 2.0f, 30.0f * i), *m_PhysicsWorld));
	}
}

Game::~Game() {
	Renderer::Destroy();

	delete character;
	delete camera;
	delete m_PhysicsWorld;

	character = nullptr;
	camera = nullptr;
	m_PhysicsWorld = nullptr;
}

void Game::LoadShaders() const {
	Shader::Load("Flat", "Assets/Shaders/Flat.vert.glsl", "Assets/Shaders/Flat.frag.glsl");
}

void Game::OnUpdate() {
	m_PhysicsWorld->Step(Time::GetDeltaTime(), 6, 2);

	for (auto& gameObject : gameObjects) {
		gameObject->OnUpdate();
	}
	character->OnUpdate();
}

void Game::OnRender() {
	ImGui::ShowMetricsWindow();

	Renderer::BeginCamera(camera);

	//Renderer::BeginBatch();
	for (auto& gameObject : gameObjects) {
		gameObject->OnRender();
	}
	//Renderer::EndBatch();

	character->OnRender();
}