#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
	glm::mat4 m_Projection;
	glm::mat4 m_View;

public:
	Camera(unsigned int width, unsigned int height);

public:
	inline const glm::mat4& GetProjection() { return m_Projection; }
	inline const glm::mat4& GetView() { return m_View; }

public:
	void SetView(const glm::vec2& position);
};