#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader
{
private:
	unsigned int m_ShaderID;
	std::unordered_map<const char*, int> m_UniformLocationCache;
public:
	Shader(const char* vertPath, const char* fragPath);
	Shader(const char* vertPath, const char* fragPath, const char* geoPath);
	~Shader();

	void setUniformMat4f(const char* uniformName, const glm::mat4& mat);

	void bind() const;
	void unbind() const;
private:
	unsigned int compileShader(unsigned int type, const std::string& src);
	unsigned int createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);

	int getUniformLocation(const char* uniformName);
};