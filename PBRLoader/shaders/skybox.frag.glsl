#version 450 core

layout (location = 0) out vec4 colour;

in vec3 texCoords;

uniform samplerCube skybox;

void main()
{
	colour = texture(skybox, texCoords);
}