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
public:
	Window();
	~Window();

	void swapBuffer();
	
	inline int getBufferWidth() const { return m_BufferWidth; }
	inline int getBufferHeight() const { return m_BufferHeight; }
	inline bool* getKey() { return m_Keys; }
	inline const glm::mat4& getProjectionMatrix() const { return m_Proj; }

	bool shouldClose() const; 
	void pollEvents();
	void clearBuffer();

	static void keyCallback(GLFWwindow* windows, int key, int code, int action, int mode);
};