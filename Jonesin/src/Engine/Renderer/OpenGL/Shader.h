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
	void GetActiveUniform()const;//Functions to Get All Active Uniform
	//Functions for setting uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name,float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat3f(const std::string& name, unsigned int count, unsigned char normalized, const float* value);
	void SetUniformMat4f(const std::string& name, unsigned int count,unsigned char normalized,const float* value);
	
	static std::shared_ptr<Shader> Create(const std::string& vs_filePath,const std::string& fs_filePath) { return std::make_shared<Shader>(vs_filePath,fs_filePath); }
private:
	std::string m_fs_filePath;
	std::string m_vs_filePath;
	shader_src m_src;
	GLuint m_ShaderID;
};
class ShaderLibrary
{
	const std::shared_ptr<Shader>& GetShaderByName(const std::string& name);
	void Add(const std::string& name,const std::shared_ptr<Shader>& shader);
	const std::shared_ptr<Shader>& Load(const std::string& name ,const std::shared_ptr<Shader>& shader);

	bool Exists(const std::string& shader_name);

	

private:
	std::unordered_map<std::string, std::shared_ptr<Shader>>m_Shaders;
};

