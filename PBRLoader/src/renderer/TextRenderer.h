#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <map>
#include "Text.h"
#include <Shader.h>

struct Character {
	unsigned int texID;
	glm::vec2 size;
	glm::vec2 bearing;
	unsigned int advance;
};

class TextRenderer 
{
private:
	std::map<char, Character> characters;
	unsigned int tex[128];
public:
	TextRenderer(const char* fontPath);
	~TextRenderer();

	void renderText(const Text& text, Shader& shader);
};
