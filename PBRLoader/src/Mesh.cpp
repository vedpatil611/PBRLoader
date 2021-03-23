#include "Mesh.h"

#include "Camera.h"
#include "Shader.h"
#include "Window.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(float* vertexData, unsigned int vertexCount, unsigned short* indicies, unsigned int indexCount, Shader* shader)
	:m_IndexCount(indexCount), m_Shader(shader), m_Translate(0.0f, 0.0f, 0.0f), m_Rotate(0.0f, 0.0f, 0.0f), m_Scale(1.0f, 1.0f, 1.0f)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData[0]) * vertexCount, vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies[0]) * indexCount, indicies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
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

void Mesh::draw(const Window* window, const Camera* camera)
{
	m_Shader->bind();
	m_Shader->setUniformMat4f("uProj", window->getProjectionMatrix());
	m_Shader->setUniformMat4f("uView", camera->getViewMatrix());

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
	m_Shader->unbind();
}
