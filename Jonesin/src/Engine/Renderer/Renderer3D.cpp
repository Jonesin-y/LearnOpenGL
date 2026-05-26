#include "pch.h"
#include "Renderer3D.h"
#include"Camera.h"
#include"Material.h"
#include"Meshs/Mesh.h"
#include"Environment.h"
Renderer3D::Renderer3D(const Ref(Camera)& camera, const Ref(Environment)& environment)
	:m_Camera(camera),m_Environment(environment)
{

}

void Renderer3D::BeginScene()
{

}

void Renderer3D::SubmitMesh(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, glm::mat4 transformation)
{

	mesh->SetMaterial();
}

void Renderer3D::EndScene()
{

}
