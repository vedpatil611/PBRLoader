#pragma once

class Mesh
{
private:
	unsigned int m_VAO, m_VBO, m_IBO;
	unsigned int m_IndexCount;
	class Shader* m_Shader;
public:
	Mesh(float* vertexData, unsigned int vertexCount, unsigned short* indicies, unsigned int indexCount, class Shader* shader);
	~Mesh();

	void draw();
};