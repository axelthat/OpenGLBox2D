#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"

class Wall : public GameObject {
public:
	const glm::vec4 m_Color;
	b2World& m_PhysicsWorld;
	b2Body* m_Body;

public:
	Wall(const glm::vec2& position, b2World& physicsWorld);

public:
	void OnUpdate() override;
	void OnRender() override;
};