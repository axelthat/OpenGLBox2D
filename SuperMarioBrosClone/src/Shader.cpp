#include <iostream>

#include "Shader.h"
#include "Util.h"
#include "Exceptions/ShaderLoadException.h"
#include "Exceptions/ShaderCompileException.h"

std::unordered_map<std::string, Shader> Shader::m_Shaders;

void Shader::Load(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	std::string vertexShaderContents;
	std::string fragmentShaderContents;

	try {
		vertexShaderContents = Util::ReadFile(vertexShaderPath);
		fragmentShaderContents = Util::ReadFile(fragmentShaderPath);
	}
	catch (const std::exception& e) {
		throw ShaderLoadException(e.what());
	}

	m_Shaders.emplace(
		std::piecewise_construct,
		std::forward_as_tuple(name),
		std::forward_as_tuple(vertexShaderContents.c_str(), fragmentShaderContents.c_str())
	);
}

Shader& Shader::Get(const std::string& name) {
	auto it = m_Shaders.find(name);
	if (it != m_Shaders.end()) {
		return it->second;
	}
}

Shader::Shader(const char* vertexShader, const char* fragmentShader) {
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShader, nullptr);
	glCompileShader(vs);
	ValidateShader(vs);

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShader, nullptr);
	glCompileShader(fs);
	ValidateShader(fs);

	m_Id = glCreateProgram();
	glAttachShader(m_Id, vs);
	glAttachShader(m_Id, fs);
	glLinkProgram(m_Id);
	ValidateProgram(m_Id);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader() {
	glDeleteProgram(m_Id);
}

void Shader::ValidateProgram(unsigned int id) const
{
	int result;
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	if (!result) {
		int length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetProgramInfoLog(id, length, &length, message);
		std::string err(message);

		delete[] message;
		message = nullptr;

		throw ShaderCompileException(err);
	}
}

void Shader::ValidateShader(unsigned int id) const
{
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::string err(message);

		delete[] message;
		message = nullptr;

		throw ShaderCompileException(err);
	}
}

unsigned int Shader::GetUniformCache(const std::string& name)
{
	if (m_UniformCache.find(name) == m_UniformCache.end())
		return m_UniformCache[name];
	unsigned int location = glGetUniformLocation(m_Id, name.c_str());
	m_UniformCache[name] = location;
	return location;
}

void Shader::SetBool(const std::string& name, bool value) {
	glUniform1i(GetUniformCache(name), value);
}

void Shader::SetInt(const std::string& name, int value)
{
	glUniform1i(GetUniformCache(name), value);
}

void Shader::SetInt(const std::string& name, int count, int* value)
{
	glUniform1iv(GetUniformCache(name), count, value);
}

void Shader::SetFloat(const std::string& name, float value)
{
	glUniform1f(GetUniformCache(name), value);
}

void Shader::SetVector2(const std::string& name, glm::vec2 value)
{
	glUniform2f(GetUniformCache(name), value.x, value.y);
}

void Shader::SetVector3(const std::string& name, glm::vec3 value)
{
	glUniform3f(GetUniformCache(name), value.x, value.y, value.z);
}

void Shader::SetVector4(const std::string& name, glm::vec4 value)
{
	glUniform4f(GetUniformCache(name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const std::string& name, glm::mat4 value)
{
	glUniformMatrix4fv(GetUniformCache(name), 1, false, glm::value_ptr(value));
}