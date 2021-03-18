#include "Window.h"

#include <cstdio>
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

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
	m_Proj = glm::perspective(glm::radians(65.0f), (float) m_BufferWidth / m_BufferHeight, 0.1f, 100.0f);

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetKeyCallback(m_Window, &Window::keyCallback);
	glfwSetMouseButtonCallback(m_Window, &Window::mouseKeyCallback);
	glfwSetCursorPosCallback(m_Window, &Window::mousePositionCallback);
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

float Window::getXChange()
{
	float change = m_xChange;
	m_xChange = 0;
	return change;
}

float Window::getYChange()
{
	float change = m_yChange;
	m_yChange = 0;
	return change;
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::clearBuffer()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void Window::mouseKeyCallback(GLFWwindow* window, int key, int action, int mods)
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

void Window::mousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	currentWindow->m_xChange = xPos - currentWindow->m_LastX;
	currentWindow->m_yChange = currentWindow->m_LastY - yPos;

	currentWindow->m_LastX = xPos;
	currentWindow->m_LastY = yPos;
}
