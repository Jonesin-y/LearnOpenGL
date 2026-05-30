#pragma once
#include <glm/glm.hpp>
class Shader;
struct lightSource
{
	alignas(4)  int enableLight = true;
	alignas(4)  float radius = 5.0f;
	alignas(4)  float intensity = 50.0f;
	alignas(4)  float outCut = cos(glm::radians(17.5f));
	alignas(4)  float innerCut = cos(glm::radians(10.0f));

	alignas(4) int padding1 = -1;
	alignas(4) int padding2 = -1;
	alignas(4) int padding3 = -1;

	alignas(16) glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
	alignas(16) glm::vec3 direction = glm::vec3(1.0f, 1.0f, 1.0f);
	alignas(16) glm::vec3 ambient = glm::vec3(0.2f,0.2f,0.2f); 
	alignas(16) glm::vec3 diffuse = glm::vec3(0.6f,0.6f,0.6f);
	alignas(16) glm::vec3 specular = glm::vec3(1.0f,1.0f,1.0f);

	
	void ApplyToShader(std::shared_ptr<Shader>& shader, const std::string& lightSource_name);
	
};

