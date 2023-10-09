#pragma once

#include <GLFW/glfw3.h>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Input {
private:
	static bool m_Keys[GLFW_KEY_LAST + 1];
	static bool m_KeysUp[GLFW_KEY_LAST + 1];
	static int m_Action;

public:
	static inline void SetKey(int key, bool state) { m_Keys[key] = state; }
	static inline void SetKeyUp(int key, bool state) { m_KeysUp[key] = state; }
	static inline void SetAction(int action) { m_Action = action; }

	static bool GetKey(int key);
	static bool GetKeyDown(int key);
};