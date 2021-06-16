#pragma once

#include <glm/glm.hpp>
#include <string>

class Text {
private:
	std::string text;
	unsigned VAO;
	unsigned VBO;
	float x, y;
	float scale;
	glm::vec4 colour;
public:
	Text(const std::string& text, float x, float y, float scale, const glm::vec4& colour);
};