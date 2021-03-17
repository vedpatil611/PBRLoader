#include "Shader.h"

#include <glad/glad.h>
#include <utils/File.h>

Shader::Shader(const char* vertPath, const char* fragPath)
{
	m_ShaderID = createShaderProgram(Utils::readFile(vertPath), Utils::readFile(fragPath));
}

Shader::Shader(const char* vertPath, const char* fragPath, const char* geoPath)
{
	m_ShaderID = createShaderProgram(Utils::readFile(vertPath), Utils::readFile(fragPath), Utils::readFile(geoPath));
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& src)
{
	unsigned int id = glCreateShader(type);
	const char* code = src.c_str();
	glShaderSource(id, 1, &code, nullptr);
	glCompileShader(id);

	#ifdef DEBUG
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);
			printf("Failed to compile %s shader: %s", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
			glDeleteShader(id);
			delete[] message;
			return 0;
		}
	#endif // DEBUG

	return id;
}

unsigned int Shader::createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteProgram(vs);
	glDeleteProgram(fs);

	return program;
}

unsigned int Shader::createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	unsigned int gs = compileShader(GL_GEOMETRY_SHADER, geometryShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glAttachShader(program, gs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteProgram(vs);
	glDeleteProgram(fs);
	glDeleteProgram(gs);

	return program;
}
