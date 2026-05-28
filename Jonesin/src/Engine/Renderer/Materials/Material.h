#pragma once
#include"Core.h"
#include <glm/glm.hpp>
#include<glad/glad.h>

class Shader;
class Material
{
public:
	Material(const std::string& Name);
	float shininess;
	glm::vec3 colorAmbient = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 colorDiffuse = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 colorSpecular= glm::vec3(1.0f,1.0f,1.0f);
	
	GLint diffuseMapID = 1;
	GLint specularMapID = 2;
	GLint emissionMapID = 3;
	void Upload();
	inline void SetShader(const Ref(Shader)& shader) { m_Shader = shader; }

private:
	std::string m_Name;
	Ref(Shader) m_Shader;
};

