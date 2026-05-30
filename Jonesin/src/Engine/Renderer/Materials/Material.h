#pragma once
#include"Core.h"
#include"Shader.h"
#include <glm/glm.hpp>
#include<glad/glad.h>

class Shader;
class Material
{
public:
	Material(const std::string& Name);
	Material();
	float shininess = 32.0f;
	glm::vec3 colorAmbient = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 colorDiffuse = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 colorSpecular= glm::vec3(1.0f,1.0f,1.0f);
	
	GLint diffuseMapID = 1;
	GLint specularMapID = 2;
	GLint emissionMapID = 3;
	void Upload(const std::string& Name);
	void Upload();
	void Bind();
	void SetShader(const Ref(Shader) shader);
	inline Ref(Shader)& GetShader() { return m_Shader; }
	inline std::string GetName() { return m_Name; }

private:
	std::string m_Name;
	Ref(Shader) m_Shader;
};

