#include "pch.h"
#include "Shader.h"
#include "Material.h"


void Material::ApplyToShader(Shader& shader,const std::string& material_name)//Only work after relevant shader was used
{
	shader.SetUniform1f(material_name + ".shininess", shininess);
	shader.SetUniform3f(material_name + ".colorAmbient", colorAmbient.x, colorAmbient.y, colorAmbient.z);
	shader.SetUniform3f(material_name + ".colorDiffuse", colorDiffuse.x, colorDiffuse.y, colorDiffuse.z);
	shader.SetUniform3f(material_name + ".colorSpecular", colorSpecular.x, colorSpecular.y, colorSpecular.z);
	shader.SetUniform1i(material_name + ".diffuseMapID", diffuseMapID);
	shader.SetUniform1i(material_name + ".specularMapID",specularMapID);
	shader.SetUniform1i(material_name + ".emissionMapID", emissionMapID);

}

