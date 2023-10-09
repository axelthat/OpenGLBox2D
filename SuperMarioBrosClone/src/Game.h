#pragma once

#include <vector>
#include <box2d/box2d.h>

#include "Camera.h"
#include "Character.h"
#include "GameObject.h"

class Game {
private:
	b2World* m_PhysicsWorld;

	Character* character;
	Camera* camera;

	std::vector<std::unique_ptr<GameObject>> gameObjects;

public:
	Game(unsigned int width, unsigned int height);
	~Game();

private:
	void LoadShaders() const;

public:
	void OnUpdate();
	void OnRender();
};