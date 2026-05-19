#pragma once
#include <glm/glm.hpp>
#include<glad/glad.h>

class Shader;
struct Material
{

	float shininess;
	glm::vec3 colorAmbient = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 colorDiffuse = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 colorSpecular= glm::vec3(1.0f,1.0f,1.0f);
	
	GLint diffuseMapID = 1;
	GLint specularMapID = 2;

	GLint emissionMapID = 3;
	void ApplyToShader(Shader& shader,const std::string& material_name);
};

