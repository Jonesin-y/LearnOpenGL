#include "pch.h"
#include"Buffer.h"
#include "Renderer3D.h"
#include"Camera.h"
#include"Materials/Material.h"
#include"Meshs/Mesh.h"
#include"Environment.h"
#include<GLFW/glfw3.h>
Renderer3D::Renderer3D(const Ref(Camera)& camera, const Ref(Environment)& environment)
	:m_Camera(camera),m_Environment(environment)
{
	m_CameraUniformBuffer = std::make_shared<UniformBuffer>(sizeof(CameraData));
	m_EnvironmentUniformBuffer = std::make_shared<UniformBuffer>(environment->GetLightSourcesSize());
	
}

void APIENTRY Renderer3D::glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	// Ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	}

}

void Renderer3D::Init()
{
	Renderer3D::EnableOpenGLDebugging();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.05f, 0.15f, 0.2f, 0.7f);
}

void Renderer3D::EnableOpenGLDebugging()
{
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);

		// glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
}

void Renderer3D::BeginScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	CameraData cameraData(m_Camera->Position, m_Camera->GetProjection(), m_Camera->GetViewMatrix());
	//UBO绑定点静态绑定数据
	m_CameraUniformBuffer->Submit(&cameraData, 0, sizeof(CameraData));
	m_EnvironmentUniformBuffer->Submit(m_Environment->GetLightSources().data(), 0, m_Environment->GetLightSourcesSize());
}

void Renderer3D::SubmitMesh(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, glm::mat4 transformation)
{
	mesh->Bind();
	mesh->SetMaterial(material);
	material->Upload();
	material->GetShader()->SetUniformMat4f("u_Model", 1, GL_FALSE, &transformation[0][0]);
	glm::mat3 normalMat = (glm::mat3)glm::transpose(glm::inverse(transformation));
	material->GetShader()->SetUniformMat3f("u_normalMat", 1, GL_FALSE, &normalMat[0][0]);
	glDrawElements(GL_TRIANGLES, mesh->GetIndices().size(), GL_UNSIGNED_INT, nullptr);
}

void Renderer3D::EndScene()
{
}
