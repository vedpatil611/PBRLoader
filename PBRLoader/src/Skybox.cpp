#include "Skybox.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <FreeImage/FreeImage.h>
#include <stdexcept>

#include "Camera.h"
#include "Window.h"

Skybox::Skybox(const char** faceLocations, Shader* shader)
	:m_Shader(shader)
{
	glGenTextures(1, &m_TexID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TexID);

	int height, width, bitDepth;
	for (int i = 0; i < 6; ++i)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib(0);
		BYTE* bits(0);

		fif = FreeImage_GetFileType(faceLocations[i], 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(faceLocations[i]);

		if (fif == FIF_UNKNOWN)
			throw std::runtime_error("File type no supported");

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, faceLocations[i]);

		if (!dib)
			throw std::runtime_error("Failed to load texture");

		FreeImage_FlipVertical(dib);

		bits = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height= FreeImage_GetHeight(dib);
		bitDepth = FreeImage_GetBPP(dib);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);

		FreeImage_Unload(dib);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	float skyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	unsigned int skyboxIndices[] = {
		0, 1, 2,
		2, 1, 3,
		2, 3, 5,
		5, 3, 7,
		5, 7, 4,
		4, 7, 6,
		4, 6, 0,
		0, 6, 1,
		4, 0, 5,
		5, 0, 2,
		1, 6, 3,
		3, 6, 7
	};

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glEnableVertexArrayAttrib(m_VAO, 0);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Skybox::~Skybox()
{
}

void Skybox::draw(const Window* window, const Camera* camera)
{
	m_Shader->bind();
	m_Shader->setUniformMat4f("uProj", window->getProjectionMatrix());
	m_Shader->setUniformMat4f("uView", glm::mat4(glm::mat3(camera->getViewMatrix())));

	glDepthMask(GL_FALSE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TexID);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glDepthMask(GL_TRUE);
	m_Shader->unbind();
}
