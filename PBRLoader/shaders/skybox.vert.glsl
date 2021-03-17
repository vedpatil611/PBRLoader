#version 450 core

layout (location = 0) in vec3 position;

out vec3 texCoords;

uniform mat4 uView = mat4(1.0);
uniform mat4 uProj = mat4(1.0);

void main()
{
	gl_Position = uProj * uView * vec4(position, 1.0f);
	texCoords = position;
}
