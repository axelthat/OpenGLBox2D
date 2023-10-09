#pragma once

#include <glm/glm.hpp>

class GameObject {
protected:
	glm::vec2 m_Position;
	float m_Rotation;
	float m_Scale;

public:
	inline const glm::vec2& GetPosition() const { return m_Position; }
	inline const float& GetRotation() const { return m_Rotation; }
	inline const float& GetScale() const { return m_Scale; }

public:
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
};