#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec2 texCoords;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
	gl_Position = uProj * uView * uModel * vec4(pos, 1.0f);
	texCoords = uv;
}