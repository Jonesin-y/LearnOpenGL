#include "pch.h"
#include "Shader.h"
#include "Material.h"


Material::Material(const std::string& name)
	:m_Name(name)
{

}

void Material::Upload()//Only work after relevant shader was used
{
	m_Shader->SetUniform1f(m_Name + ".shininess", shininess);
	m_Shader->SetUniform3f(m_Name + ".colorAmbient", colorAmbient.x, colorAmbient.y, colorAmbient.z);
	m_Shader->SetUniform3f(m_Name + ".colorDiffuse", colorDiffuse.x, colorDiffuse.y, colorDiffuse.z);
	m_Shader->SetUniform3f(m_Name + ".colorSpecular", colorSpecular.x, colorSpecular.y, colorSpecular.z);
	m_Shader->SetUniform1i(m_Name + ".diffuseMapID", diffuseMapID);
	m_Shader->SetUniform1i(m_Name + ".specularMapID",specularMapID);
	m_Shader->SetUniform1i(m_Name + ".emissionMapID", emissionMapID);

}

