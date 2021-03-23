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

	inline glm::vec3 getTranslation() const { return m_Translate; }
	inline glm::vec3 getRotation() const { return m_Rotate; }
	inline glm::vec3 getScaling() const { return m_Scale; }

	void draw(const class Window* window, const class Camera* camera);
};