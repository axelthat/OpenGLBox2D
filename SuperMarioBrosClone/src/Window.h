#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* m_Window;

private:
	static constexpr unsigned int WINDOW_WIDTH = 1920;
	static constexpr unsigned int WINDOW_HEIGHT = 1080;

public:
	Window();
	~Window();

public:
	GLFWwindow* GetWindow() const { return m_Window; }
	inline constexpr unsigned int GetWindowWidth() { return WINDOW_WIDTH; }
	inline constexpr unsigned int GetWindowHeight() { return WINDOW_HEIGHT; }

private:
	void Terminate() const;

public:
	int LoadGL() const;
	int ShouldClose() const;
	void Clear() const;
	void SwapBuffers() const;
	void PollEvents() const;
};