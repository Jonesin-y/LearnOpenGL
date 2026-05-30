#pragma once
#include"Core.h"
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<memory>
#include<unordered_map>
#include<string>
class Camera;
class CameraController;
class UniformBuffer;
class Environment;
class Mesh;
class Material;
class Renderer3D
{
public:
	Renderer3D(const Ref(Camera)& camera, const Ref(Environment)& environment);
	~Renderer3D()=default;
	static void APIENTRY glDebugOutput(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);
	static void Init();
	static void EnableOpenGLDebugging();
	void BeginScene();
	void SubmitMesh(const std::shared_ptr<Mesh>& mesh,const std::shared_ptr<Material>& material,glm::mat4 transformation);
	void EndScene();

	inline Ref(Camera)& GetCamera() { return m_Camera; }
	inline Ref(Environment)& GetEnvironment() { return m_Environment; }
private:
	Ref(Camera) m_Camera;
	Ref(Environment)m_Environment;
	Ref(UniformBuffer)m_CameraUniformBuffer;
	Ref(UniformBuffer)m_EnvironmentUniformBuffer;
};

