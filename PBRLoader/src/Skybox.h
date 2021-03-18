#pragma once

#include "Shader.h"

class Skybox
{
private:
	Shader* m_Shader;
	unsigned int m_TexID;
	unsigned int m_VAO, m_IBO, m_VBO;
public:
	Skybox(const char** faceLocations, Shader* shader);
	~Skybox();

	void draw(const class Window* window, const class Camera* camera);
};