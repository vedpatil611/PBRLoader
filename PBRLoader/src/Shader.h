#pragma once

#include <string>

class Shader
{
private:
	unsigned int m_ShaderID;
public:
	Shader(const char* vertPath, const char* fragPath);
	Shader(const char* vertPath, const char* fragPath, const char* geoPath);
	~Shader();

	void bind() const;
	void unbind() const;
private:
	unsigned int compileShader(unsigned int type, const std::string& src);
	unsigned int createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
};