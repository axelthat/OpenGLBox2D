#include "Window.h"
#include "Exceptions/WindowCreationException.h"
#include "Exceptions/WindowInitException.h"
#include "Exceptions/GLLoadException.h"
#include "Input.h"

Window::Window():
	m_Window(nullptr)
{
	if (!glfwInit()) {
		throw WindowInitException();
	}

	m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Super Mario Bros. 1985", nullptr, nullptr);
	if (!m_Window) {
		Terminate();
		throw WindowCreationException();
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetKeyCallback(m_Window, KeyCallback);
}

Window::~Window() {
	Terminate();
}

void Window::Terminate() const {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

int Window::LoadGL() const {
	int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (version == 0) {
		throw GLLoadException();
	}

	return version;
}

int Window::ShouldClose() const {
	return glfwWindowShouldClose(m_Window);
}

void Window::Clear() const {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers() const {
	glfwSwapBuffers(m_Window);
}

void Window::PollEvents() const {
	glfwPollEvents();
}
