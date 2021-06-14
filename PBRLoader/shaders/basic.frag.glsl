#version 450 core

layout (location = 0) out vec4 colour;

in vec2 texCoords;

uniform sampler2D uTex;
//uniform vec4 uColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

void main()
{
	colour = texture(uTex, texCoords);
}