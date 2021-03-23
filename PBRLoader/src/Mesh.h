#pragma once

#include <glm/glm.hpp>

class Mesh
{
private:
	unsigned int m_VAO, m_VBO, m_IBO;
	unsigned int m_IndexCount;
	glm::vec3 m_Translate;
	glm::vec3 m_Rotate;
	glm::vec3 m_Scale;
	class Shader* m_Shader;	
public:
	Mesh(float* vertexData, unsigned int vertexCount, unsigned short* indicies, unsigned int indexCount, class Shader* shader);
	~Mesh();

	void setTranslation(glm::vec3 translation);
	void setRotation(glm::vec3 rotation);
	void setScaling(glm::vec3 scaling);

	void draw(const class Window* window, const class Camera* camera);
};