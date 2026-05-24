#include "pch.h"
#include "Shader.h"

Shader::Shader(const std::string& vs_filePath,const std::string& fs_filePath)
	: m_vs_filePath(vs_filePath),m_fs_filePath(fs_filePath)
{
	m_src.vs = LoadShaderFromFile(m_vs_filePath);
	m_src.fs = LoadShaderFromFile(m_fs_filePath);
	m_ShaderID = CreateShader(m_src.vs, m_src.fs);
	Bind();
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}

std::string Shader::LoadShaderFromFile(const std::string& filePath)
{
	std::ifstream stream(filePath);
	if (!stream.is_open())
	{
		std::cout << "读取失败!" << std::endl;
		return "";
	}
	std::stringstream sstream;
	std::string line;
	while (getline(stream, line))
	{
		sstream << line << '\n';
	}
	return sstream.str();
}

GLuint Shader::CompileShader(GLenum type, const std::string& src)
{
	GLuint id = glCreateShader(type);
	const char* src_c = src.c_str();
	glShaderSource(id, 1, &src_c, NULL);
	glCompileShader(id);
	//Shader compile error log
	GLint result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length);
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed To Compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader! ";
		std::cout << "ERROR:" << message << std::endl;

	}
	return id;
	
}

GLuint Shader::CreateShader(const std::string& vs_src, const std::string& fs_src)
{
	GLuint id = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vs_src);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fs_src);
	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);
	//shader link error log
	GLint result;
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message= (char*)alloca(length);
		glGetProgramInfoLog(id, length, &length, message);
		std::cout << "LINK ERROR! DETAIL: " << message << std::endl;
	}

	glValidateProgram(id);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return id;
}
void Shader::ShaderLog()
{
	std::cout << m_src.vs<< std::endl;
	std::cout << m_src.fs<< std::endl;
}
void Shader::Bind()
{
	glUseProgram(m_ShaderID);
}
void Shader::UnBind()
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glProgramUniform1i(m_ShaderID,location, value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glProgramUniform1f(m_ShaderID,location, value);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glProgramUniform3f(m_ShaderID,location, v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glProgramUniform4f(m_ShaderID,location, v0, v1, v2, v3);
}

void Shader::SetUniformMat3f(const std::string& name, unsigned int count, unsigned char normalized, const float* value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glProgramUniformMatrix3fv(m_ShaderID,location, count, normalized, value);
}

void Shader::SetUniformMat4f(const std::string& name, unsigned int count, unsigned char normalized, const float* value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glProgramUniformMatrix4fv(m_ShaderID,location, count, normalized, value);
}

const std::shared_ptr<Shader>& ShaderLibrary::GetShaderByName(const std::string& name)
{
	if (Exists(name)) return m_Shaders[name];
	return nullptr;
}



void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
	if (Exists(name))
	{
		std::cout << "Fail to Add Shader because it's already exists in ShaderLibrary!" << std::endl;
		return;
	}
	m_Shaders[name] = shader;
}

const std::shared_ptr<Shader>& ShaderLibrary::Load(const std::string& name, const std::shared_ptr<Shader>& shader)
{
	Add(name, shader);
	return shader;
	
}

bool ShaderLibrary::Exists(const std::string& shader_name)
{
	if (m_Shaders.find(shader_name) == m_Shaders.end())
	{
		std::cout << "shaderLibrary doesn't exists " << shader_name << "Shader!" << std::endl;
		return false;
	}
	std::cout << "shaderLibrary  exist " << shader_name << "Shader!" << std::endl;
	return true;
}
