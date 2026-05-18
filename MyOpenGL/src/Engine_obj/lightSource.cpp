#include "pch.h"
#include"Shader.h"
#include "lightSource.h"

lightSource::lightSource(glm::vec4 Position, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular)
	:position(Position),ambient(Ambient),diffuse(Diffuse),specular(Specular)
{

}

void lightSource::ApplyToShader(Shader& shader, const std::string& lightSource_name)
{
	shader.SetUniform4f(lightSource_name+ ".position", position.x,position.y,position.z,position.w);
	shader.SetUniform3f(lightSource_name+ ".ambient", ambient.x, ambient.y, ambient.z);
	shader.SetUniform3f(lightSource_name+ ".diffuse", diffuse.x, diffuse.y, diffuse.z);
	shader.SetUniform3f(lightSource_name+ ".specular", specular.x, specular.y, specular.z);
}
