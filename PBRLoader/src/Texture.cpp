#include "Texture.h"

#include <stdexcept>
#include <glad/glad.h>
#include <FreeImage/FreeImage.h>

Texture::Texture(const char* texPath)
	:m_Width(0), m_Heigth(0), m_BPP(0)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib(0);
	BYTE* bits(0);

	fif = FreeImage_GetFileType(texPath, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(texPath);

	if (fif == FIF_UNKNOWN)
		throw std::runtime_error("File type no supported");

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, texPath);

	if (!dib)
		throw std::runtime_error("Failed to load texture");

	bits = FreeImage_GetBits(dib);
	m_Width = FreeImage_GetWidth(dib);
	m_Heigth = FreeImage_GetHeight(dib);

	if(bits == 0 || m_Width == 0 || m_Heigth == 0)
		throw std::runtime_error("Failed to load texture");

	glGenTextures(1, &m_TexID);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);

	FreeImage_Unload(dib);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TexID);
}

void Texture::bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 +  slot);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
