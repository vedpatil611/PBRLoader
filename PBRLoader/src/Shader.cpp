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

void Shader::setUniform1i(const char* uniformName, int uniformData)
{
	glUniform1i(getUniformLocation(uniformName), uniformData);
}

void Shader::setUniform4f(const char* uniformName, float f1, float f2, float f3, float f4)
{
	glUniform4f(getUniformLocation(uniformName), f1, f2, f3, f4);
}

void Shader::setUniformMat4f(const char* uniformName, const glm::mat4& mat)
{
	glUniformMatrix4fv(getUniformLocation(uniformName), 1, false, &mat[0][0]);
}

void Shader::bind() const
{
	glUseProgram(m_ShaderID);
}

void Shader::unbind() const
{
	glUseProgram(0);
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
			printf("Failed to compile %s shader: %s\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
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

	glDeleteShader(vs);
	glDeleteShader(fs);

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

	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(gs);

	return program;
}

int Shader::getUniformLocation(const char* uniformName)
{
	if (m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end())
		return m_UniformLocationCache[uniformName];

	int location = glGetUniformLocation(m_ShaderID, uniformName);
	if (location == -1)
		printf("\033[1;33m Warning: uniform %s not found\n\033[0;39m", uniformName);

	return location;
}
