#include "Wall.h"
#include "Renderer.h"
#include "Util.h"

Wall::Wall(const glm::vec2& position, b2World& physicsWorld):
	m_Color({
		Util::GetRandomNumber(0.0f, 1.0f),
		Util::GetRandomNumber(0.0f, 1.0f),
		Util::GetRandomNumber(0.0f, 1.0f),
		1.0f
	}), m_PhysicsWorld(physicsWorld)
{
	m_Position = glm::vec2(position.x, position.y);
	m_Rotation = 0.0f;
	m_Scale = 50.0f;

	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.Set(Util::PixelToMeter(m_Position.x), Util::PixelToMeter(m_Position.y));

	m_Body = m_PhysicsWorld.CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(Util::PixelToMeter(m_Scale / 2.0f), Util::PixelToMeter(m_Scale / 2.0f));

	m_Body->CreateFixture(&shape, 0.0f);
}

void Wall::OnUpdate() {

}

void Wall::OnRender() {
	Renderer::DrawQuad(m_Position, m_Rotation, m_Scale, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}