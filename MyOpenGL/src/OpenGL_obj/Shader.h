#pragma once
#include<string>
#include<glad/glad.h>
class shader_src
{
public:
	std::string vs;
	std::string fs;

};

class Shader
{
public:
	Shader(const std::string& vs_filePath,const std::string& fs_filePath);
	~Shader();

	std::string LoadShaderFromFile(const std::string& filePath);
	GLuint CompileShader(GLenum type, const std::string& src);
	GLuint CreateShader(const std::string& vs_src, const std::string& fs_src);
	inline GLuint GetShaderID() { return m_ShaderID; };
	void ShaderLog();
	void Bind();
	void UnBind();
	//Functions for setting uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name,float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat3f(const std::string& name, unsigned int count, unsigned char normalized, const float* value);
	void SetUniformMat4f(const std::string& name, unsigned int count,unsigned char normalized,const float* value);
	
private:
	std::string m_fs_filePath;
	std::string m_vs_filePath;
	shader_src m_src;
	GLuint m_ShaderID;
};

