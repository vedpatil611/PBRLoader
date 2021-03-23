#version 450 core

layout (location = 0) in vec3 pos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
	gl_Position = uProj * uView * uModel * vec4(pos, 1.0f);
}