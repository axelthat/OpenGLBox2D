#include <GLFW/glfw3.h>

#include "Time.h"

float Time::m_DeltaTime = 0.0f;
float Time::m_CurrentTime = 0.0f;
float Time::m_LastTime = 0.0f;

void Time::Init() {
	m_CurrentTime = glfwGetTime();
	m_DeltaTime = m_CurrentTime - m_LastTime;
	m_LastTime = m_CurrentTime;
}