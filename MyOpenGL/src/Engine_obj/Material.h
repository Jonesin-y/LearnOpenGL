#pragma once
#include <glm/glm.hpp>
#include<glad/glad.h>

class Shader;
struct Material
{
	Material(float Shininess, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);
	Material(float MapShininess, GLint DiffuseMap2D, GLint SpecularMapID);
	Material(float MapShininess, GLint DiffuseMap2D, GLint SpecularMapID,GLint EmissionMapID);
	float shininess;
	glm::vec3 colorAmbient;
	glm::vec3 colorDiffuse;
	glm::vec3 colorSpecular;
	
	GLint diffuseMapID;
	GLint specularMapID;

	GLint emissionMapID;
	void ApplyToShader(Shader& shader,const std::string& material_name);
};

