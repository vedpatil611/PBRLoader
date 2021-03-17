#include "Window.h"

#include <cstdio>
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window()
	:m_Width(1280), m_Height(720)
{
	if (!glfwInit())
	{
		printf("GLFW initilzation failed\n");
		glfwTerminate();
		return;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, "PBR Loader", nullptr, nullptr);

	if (!m_Window)
	{
		printf("Failed to create window");
		glfwTerminate();
		return;
	}

	glfwGetFramebufferSize(m_Window, &m_BufferWidth, &m_BufferHeight);
	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to init glad");

	glViewport(0, 0, m_BufferWidth, m_BufferHeight);

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetKeyCallback(m_Window, &Window::keyCallback);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::swapBuffer()
{
	glfwSwapBuffers(m_Window);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::keyCallback(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			currentWindow->getKey()[key] = true;
		}
		if (action == GLFW_RELEASE)
		{
			currentWindow->getKey()[key] = false;
		}
	}
}
