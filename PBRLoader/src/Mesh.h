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
	glm::vec4 m_Colour;
	class Shader* m_Shader;
	class Texture* m_Texture = nullptr;
	class Texture* t_Texture;
public:
	Mesh(float* vertexData, unsigned int vertexCount, unsigned short* indicies, unsigned int indexCount, class Shader* shader);
	~Mesh();

	void setTranslation(glm::vec3 translation);
	void setRotation(glm::vec3 rotation);
	void setScaling(glm::vec3 scaling);
	void setColour(glm::vec4 colour);
	void setTexture(class Texture* texture);

	inline glm::vec3 getTranslation() const { return m_Translate; }
	inline glm::vec3 getRotation() const { return m_Rotate; }
	inline glm::vec3 getScaling() const { return m_Scale; }
	inline glm::vec4 getColour() const { return m_Colour; }

	void draw(const class Window* window, const class Camera* camera);
};