#include "pch.h"
#include"Buffer.h"
#include "Renderer3D.h"
#include"Camera.h"
#include"Materials/Material.h"
#include"Meshs/Mesh.h"
#include"Environment.h"
Renderer3D::Renderer3D(const Ref(Camera)& camera, const Ref(Environment)& environment)
	:m_Camera(camera),m_Environment(environment)
{
	m_CameraUniformBuffer = std::make_shared<UniformBuffer>(2 * sizeof(glm::mat4));
	m_EnvironmentUniformBuffer = std::make_shared<UniformBuffer>(environment->GetLightSourcesSize());
}

void Renderer3D::BeginScene()
{
	std::vector<glm::mat4> CameraMat = { m_Camera->GetProjection(),m_Camera->GetViewMatrix() };
	m_CameraUniformBuffer->Submit(CameraMat.data(), 0,2 * sizeof(glm::mat4));
	m_EnvironmentUniformBuffer->Submit(m_Environment->GetLightSources().data(), 0, m_Environment->GetLightSourcesSize());

}

void Renderer3D::SubmitMesh(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, glm::mat4 transformation)
{

	mesh->SetMaterial(material);
}

void Renderer3D::EndScene()
{

}
