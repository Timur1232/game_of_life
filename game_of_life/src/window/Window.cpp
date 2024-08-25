#include "Window.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>


GLFWwindow* Window::s_window;

int Window::initialize(int width, int height, const char* title)
{
	glewExperimental = GL_TRUE;

	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	s_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!s_window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(s_window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height);

	return 0;
}

void Window::terminate()
{
	glfwTerminate();
}

bool Window::isShouldClose()
{
	return glfwWindowShouldClose(s_window);
}

void Window::setShouldClose(bool flag)
{
	glfwSetWindowShouldClose(s_window, flag);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(s_window);
}