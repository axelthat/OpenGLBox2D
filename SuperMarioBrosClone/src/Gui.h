#pragma once

#include <GLFW/glfw3.h>

class Gui {
public:
	Gui(GLFWwindow* window);
	~Gui();

public:
	void OnUpdate() const;
	void OnRender() const;
};