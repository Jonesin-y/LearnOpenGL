#include "pch.h"
#include "Shader.h"
#include "Material.h"

Material::Material(float Shininess, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 colorSpecular)
	:shininess(Shininess),colorAmbient(Ambient),colorDiffuse(Diffuse),colorSpecular(colorSpecular),
	diffuseMapID(0),specularMapID(0)
{

}

Material::Material(float MapShininess, GLint DiffuseMapID, GLint SpecularMapID)
	:shininess(MapShininess), diffuseMapID(DiffuseMapID), specularMapID(SpecularMapID),
	colorAmbient(glm::vec3(1.0f, 1.0f, 1.0f)), colorDiffuse(glm::vec3(1.0f, 1.0f, 1.0f)), colorSpecular(glm::vec3(1.0f, 1.0f, 1.0f))
{

}

Material::Material(float MapShininess, GLint DiffuseMap2D, GLint SpecularMap2D, GLint EmissionMapID)
	:shininess(MapShininess), diffuseMapID(DiffuseMap2D), specularMapID(SpecularMap2D),emissionMapID(EmissionMapID),
	colorAmbient(glm::vec3(1.0f, 1.0f, 1.0f)), colorDiffuse(glm::vec3(1.0f, 1.0f, 1.0f)), colorSpecular(glm::vec3(1.0f, 1.0f, 1.0f))
{

}

void Material::ApplyToShader(Shader& shader,const std::string& material_name)
{
	shader.SetUniform1f(material_name + ".shininess", shininess);
	shader.SetUniform3f(material_name + ".colorAmbient", colorAmbient.x, colorAmbient.y, colorAmbient.z);
	shader.SetUniform3f(material_name + ".colorDiffuse", colorDiffuse.x, colorDiffuse.y, colorDiffuse.z);
	shader.SetUniform3f(material_name + ".colorSpecular", colorSpecular.x, colorSpecular.y, colorSpecular.z);
	shader.SetUniform1i(material_name + ".diffuseMapID", diffuseMapID);
	shader.SetUniform1i(material_name + ".specularMapID",specularMapID);
	shader.SetUniform1i(material_name + ".emissionMapID", emissionMapID);

}

