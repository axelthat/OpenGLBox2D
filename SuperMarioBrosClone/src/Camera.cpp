#include "Camera.h"

Camera::Camera(unsigned int width, unsigned int height) {
	m_Projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
	m_View = glm::mat4(1.0f);
}

void Camera::SetView(const glm::vec2& position) {
	m_View = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f });
}