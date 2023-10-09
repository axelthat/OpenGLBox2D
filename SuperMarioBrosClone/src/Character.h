#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"

class Character : public GameObject {
private:
	b2World& m_PhysicsWorld;
	b2Body* m_Body;

public:
	Character(b2World& physicsWorld);

public:
	void OnUpdate() override;
	void OnRender() override;
};