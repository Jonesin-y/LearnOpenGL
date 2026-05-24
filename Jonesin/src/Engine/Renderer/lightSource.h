#pragma once
#include <glm/glm.hpp>
class Shader;
struct lightSource
{
	int enableLight = true;
	float radius = 5.0f;
	float intensity = 50.0f;
	float outCut = cos(glm::radians(17.5f));
	float innerCut = cos(glm::radians(10.0f));

	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
	glm::vec3 direction = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 ambient = glm::vec3(0.2f,0.2f,0.2f); 
	glm::vec3 diffuse = glm::vec3(0.6f,0.6f,0.6f);
	glm::vec3 specular = glm::vec3(1.0f,1.0f,1.0f);
	
	void ApplyToShader(std::shared_ptr<Shader>& shader, const std::string& lightSource_name);
	
};

