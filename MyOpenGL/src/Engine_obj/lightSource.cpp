#include "pch.h"
#include"Shader.h"
#include "lightSource.h"


void lightSource::ApplyToShader(Shader& shader, const std::string& lightSource_name)//Only work after relevant shader was used
{
	shader.SetUniform1i(lightSource_name + ".enableLight", enableLight);
	shader.SetUniform3f(lightSource_name + ".position", position.x, position.y, position.z);
	shader.SetUniform3f(lightSource_name + ".direction", direction.x, direction.y, direction.z);
	shader.SetUniform3f(lightSource_name + ".ambient", ambient.x, ambient.y, ambient.z);
	shader.SetUniform3f(lightSource_name + ".diffuse", diffuse.x, diffuse.y, diffuse.z);
	shader.SetUniform3f(lightSource_name + ".specular", specular.x, specular.y, specular.z);
	shader.SetUniform1f(lightSource_name + ".radius", radius);
	shader.SetUniform1f(lightSource_name + ".intensity", intensity);
	shader.SetUniform1f(lightSource_name + ".innerCut", innerCut);
	shader.SetUniform1f(lightSource_name + ".outCut", outCut);


}


