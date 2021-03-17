#pragma once

class Texture
{
private:
	unsigned int m_TexID;
	int m_Width, m_Heigth, m_BPP;
public:
	Texture(const char* texPath);
	~Texture();

	void bind(unsigned int slot = 0);
	void unbind();
};