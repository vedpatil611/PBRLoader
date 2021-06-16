#include "TextRenderer.h"

#include <glad/glad.h>
#include <stdexcept>

TextRenderer::TextRenderer(const char* fontPath) 
{
	FT_Library ft;
	if(FT_Init_FreeType(&ft))
		throw std::runtime_error("Failed to init ft library");

	FT_Face face;
	if(FT_New_Face(ft, fontPath, 0, &face))
		throw std::runtime_error("Failed to load font");

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(128, tex);
	
	for (unsigned char c = 0; c < 128; ++c)
	{
		if(FT_Load_Char(face, c, FT_LOAD_RENDER))
			throw std::runtime_error("Failed to load glyph");

		glBindTexture(GL_TEXTURE_2D, tex[c]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
				0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		Character character = {
			tex[c],
			glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<unsigned int>(face->glyph->advance.x)
		};

		characters[c] = character;
	}
}

TextRenderer::~TextRenderer()
{
	glDeleteTextures(128, tex);
}
