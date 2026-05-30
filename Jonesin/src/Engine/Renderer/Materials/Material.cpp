#include "pch.h"
#include "Shader.h"
#include "Material.h"


Material::Material(const std::string& name)
	:m_Name(name)
{

}

Material::Material()
{

}

void Material::Upload(const std::string& Name)//Only work after relevant shader was used
{
	m_Shader->Bind();
	m_Shader->SetUniform1f(Name + ".shininess", shininess);
	m_Shader->SetUniform3f(Name + ".colorAmbient", colorAmbient.x, colorAmbient.y, colorAmbient.z);
	m_Shader->SetUniform3f(Name + ".colorDiffuse", colorDiffuse.x, colorDiffuse.y, colorDiffuse.z);
	m_Shader->SetUniform3f(Name + ".colorSpecular", colorSpecular.x, colorSpecular.y, colorSpecular.z);
	m_Shader->SetUniform1i(Name + ".diffuseMapID", diffuseMapID);
	m_Shader->SetUniform1i(Name + ".specularMapID",specularMapID);
	m_Shader->SetUniform1i(Name + ".emissionMapID", emissionMapID);

}

void Material::Upload()
{
	m_Shader->Bind();
	m_Shader->SetUniform1f(m_Name + ".shininess", shininess);
	m_Shader->SetUniform3f(m_Name + ".colorAmbient", colorAmbient.x, colorAmbient.y, colorAmbient.z);
	m_Shader->SetUniform3f(m_Name + ".colorDiffuse", colorDiffuse.x, colorDiffuse.y, colorDiffuse.z);
	m_Shader->SetUniform3f(m_Name + ".colorSpecular", colorSpecular.x, colorSpecular.y, colorSpecular.z);
	m_Shader->SetUniform1i(m_Name + ".diffuseMapID", diffuseMapID);
	m_Shader->SetUniform1i(m_Name + ".specularMapID", specularMapID);
	m_Shader->SetUniform1i(m_Name + ".emissionMapID", emissionMapID);
}

void Material::Bind()
{
	m_Shader->Bind();
}

void Material::SetShader(const Ref(Shader) shader)
{
	m_Shader = shader;
	m_Shader->Bind();
}

