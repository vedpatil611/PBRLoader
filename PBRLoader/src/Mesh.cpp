#include "Mesh.h"

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(float* vertexData, unsigned int vertexCount, unsigned short* indicies, unsigned int indexCount, Shader* shader)
	:m_IndexCount(indexCount), m_Shader(shader), m_Translate(0.0f, 0.0f, 0.0f), m_Rotate(0.0f, 0.0f, 0.0f), m_Scale(1.0f, 1.0f, 1.0f), m_Colour(1.0f, 1.0f, 1.0f, 1.0f)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexCount, indicies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (const void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	t_Texture = new Texture("assets/textures/white.png");
	m_Texture = t_Texture;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);

	delete t_Texture;
}

void Mesh::setTranslation(glm::vec3 translation)
{
	m_Translate = translation;
}

void Mesh::setRotation(glm::vec3 rotation)
{
	m_Rotate = rotation;
}

void Mesh::setScaling(glm::vec3 scaling)
{
	m_Scale = scaling;
}

void Mesh::setTexture(Texture* texture)
{
	m_Texture = texture;
}

void Mesh::setColour(glm::vec4 colour)
{
	m_Colour = colour;
}

void Mesh::draw(const Window* window, const Camera* camera)
{
	m_Shader->bind();
	m_Shader->setUniformMat4f("uProj", window->getProjectionMatrix());
	m_Shader->setUniformMat4f("uView", camera->getViewMatrix());

	m_Texture->bind(1);
	m_Shader->setUniform1i("uTex", 1);
	//m_Shader->setUniform4f("uColour", m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a);

	auto model = glm::translate(glm::mat4(1.0f), m_Translate);
	model = glm::rotate(model, glm::radians(m_Rotate[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rotate[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rotate[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, m_Scale);
	m_Shader->setUniformMat4f("uModel", model);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, nullptr);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_Texture->unbind();
	m_Shader->unbind();
}
