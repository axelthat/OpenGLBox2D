#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

class Shader {
private:
	static std::unordered_map<std::string, Shader> m_Shaders;

public:
	static void Load(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	static Shader& Get(const std::string& name);

private:
	unsigned int m_Id;
	std::unordered_map<std::string, unsigned int> m_UniformCache;

public:
	Shader(const char* vertexShader, const char* fragmentShader);
	~Shader();

public:
	inline void Bind() const { glUseProgram(m_Id); }
	inline void UnBind() const { glUseProgram(0); }

private:
	void ValidateShader(unsigned int id) const;
	void ValidateProgram(unsigned int id) const;
	unsigned int GetUniformCache(const std::string& name);

public:
	void SetBool(const std::string& name, bool value);
	void SetInt(const std::string& name, int value);
	void SetInt(const std::string& name, int count, int* value);
	void SetFloat(const std::string& name, float value);
	void SetVector2(const std::string& name, glm::vec2 value);
	void SetVector3(const std::string& name, glm::vec3 value);
	void SetVector4(const std::string& name, glm::vec4 value);
	void SetMatrix4(const std::string& name, glm::mat4 value);
};