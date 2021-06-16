#version 450 core

layout (location = 0) out vec4 outColour;

in vec2 texCoords;

uniform sampler2D tex;
uniform vec4 colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

void main()
{
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(tex, texCoords).r);
	outColour = sampled * colour;
}