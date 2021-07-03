#pragma once

#include <glm/glm.hpp>
#include <string>

class Text {
private:
	unsigned VAO;
	unsigned VBO;
public:
	std::string text;
	float x, y;
	float scale;
	glm::vec4 colour;
public:
	Text(const std::string& text, float x, float y, float scale, const glm::vec4& colour);
	~Text();

	inline unsigned int getVAO() const { return VAO; }
	inline unsigned int getVBO() const { return VBO; }
};