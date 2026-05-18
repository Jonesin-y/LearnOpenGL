#pragma once
#include <glm/glm.hpp>
class Shader;
struct lightSource
{
	lightSource(glm::vec4 Position, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);
	glm::vec4 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	
	void ApplyToShader(Shader& shader, const std::string& lightSource_name);
};

