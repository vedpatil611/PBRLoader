#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <map>

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
public:
	TextRenderer(const char* fontPath);
};
