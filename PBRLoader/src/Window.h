#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

class Window
{
private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;
	int m_BufferWidth, m_BufferHeight;
	bool m_Keys[1024] = { 0 };
	glm::mat4 m_Proj;

	float m_LastX = 0.0f, m_LastY = 0.0f;
	float m_xChange = 0.0f, m_yChange = 0.0f;
public:
	Window();
	~Window();

	void swapBuffer();
	
	inline int getBufferWidth() const { return m_BufferWidth; }
	inline int getBufferHeight() const { return m_BufferHeight; }
	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
	inline GLFWwindow* getWindow() const { return m_Window; }
	float getXChange();
	float getYChange();
	inline bool* getKey() { return m_Keys; }
	inline const glm::mat4& getProjectionMatrix() const { return m_Proj; }

	bool shouldClose() const; 
	void pollEvents();
	void clearBuffer();

	static void keyCallback(GLFWwindow* window, int key, int code, int action, int mode);
	static void mouseKeyCallback(GLFWwindow* window, int key, int action, int mods);
	static void mousePositionCallback(GLFWwindow* window, double xPos, double yPos);
};