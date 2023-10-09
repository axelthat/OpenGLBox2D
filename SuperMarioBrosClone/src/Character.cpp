#include <iostream>

#include "Character.h"
#include "Renderer.h"
#include "Time.h"
#include "Input.h"
#include "Time.h"
#include "Util.h"

Character::Character(b2World& physicsWorld) : m_PhysicsWorld(physicsWorld) {
	m_Position = glm::vec2(800.0f, 800.0f);
	m_Rotation = 45.0f;
	m_Scale = 50.0f;

	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.position.Set(Util::PixelToMeter(m_Position.x), Util::PixelToMeter(m_Position.y));

	m_Body = m_PhysicsWorld.CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(Util::PixelToMeter(m_Scale / 2.0f), Util::PixelToMeter(m_Scale / 2.0f));

	b2Fixture* fixture = m_Body->CreateFixture(&shape, 1.0f);
	fixture->SetFriction(0.3f);
}

void Character::OnUpdate() {
	const auto& newPosition = m_Body->GetPosition();
	m_Position.x = Util::MeterToPixel(newPosition.x);
	m_Position.y = Util::MeterToPixel(newPosition.y);
	m_Rotation = m_Body->GetAngle();
}

void Character::OnRender() {
	Renderer::DrawQuad(m_Position, m_Rotation, m_Scale, { 0.0f, 1.0f, 0.0f, 1.0f });
}