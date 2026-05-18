#include "pch.h"
#include "Shader.h"

Shader::Shader(const std::string& filePath)
	: m_filePath(filePath)
{
	m_src = LoadShaderFromFile(m_filePath);
	m_ShaderID = CreateShader(m_src.vs, m_src.fs);
	Bind();
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}

shader_src Shader::LoadShaderFromFile(const std::string& filePath)
{
	enum shader_type
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	shader_type type = NONE;
	std::stringstream ss[2];
	std::ifstream stream(filePath);
	std::string line;
	if (!stream.is_open())
	{
		printf("Failed to open file: %s\n", filePath.c_str());
		return { "","" };
	}
	while (getline(stream, line))
	{
		if (line.find("#vertex") != std::string::npos)
		{
			type = VERTEX;
			continue;
		}
		else if (line.find("#fragment") != std::string::npos)
		{
			type = FRAGMENT;
			continue;
		}
		if (type != NONE)
		{
			ss[type] << line << "\n";
		}
	}
	return { ss[0].str(),ss[1].str() };

}

GLuint Shader::CompileShader(GLenum type, const std::string& src)
{
	GLuint id = glCreateShader(type);
	const char* src_c = src.c_str();
	glShaderSource(id, 1, &src_c, NULL);
	glCompileShader(id);
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
	glUniform1i(location, value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniform1f(location, value);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniform3f(location, v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniform4f(location, v0, v1, v2, v3);
}

void Shader::SetUniformMat3f(const std::string& name, unsigned int count, unsigned char normalized, const float* value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniformMatrix3fv(location, count, normalized, value);
}

void Shader::SetUniformMat4f(const std::string& name, unsigned int count, unsigned char normalized, const float* value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniformMatrix4fv(location, count, normalized, value);
}
