#include <iostream>

#include "Input.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Input::SetAction(action);

	if (action == GLFW_PRESS) {
		Input::SetKey(key, true);
		Input::SetKeyUp(key, false);
	}
	else if (action == GLFW_RELEASE) {
		Input::SetKey(key, false);
		Input::SetKeyUp(key, true);
	}
}

bool Input::m_Keys[GLFW_KEY_LAST + 1];
bool Input::m_KeysUp[GLFW_KEY_LAST + 1];
int Input::m_Action;

bool Input::GetKey(int key) {
	const auto pressed = m_Keys[key];
	if (m_Action == GLFW_PRESS || m_Action == GLFW_RELEASE) {
		m_Keys[key] = false;
	}
	return pressed;
}

bool Input::GetKeyDown(int key) {
	if (!m_KeysUp[key] && m_Keys[key]) {
		return true;
	}

	return false;
}