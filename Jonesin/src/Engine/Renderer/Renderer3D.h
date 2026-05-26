#pragma once
#include"Core.h"
#include<glm/glm.hpp>
#include<memory>
class Camera;
class Environment;
class Mesh;
class Material;
class Renderer3D
{
public:
	Renderer3D(const Ref(Camera)& camera, const Ref(Environment)& environment);
	~Renderer3D()=default;
	void BeginScene();
	void SubmitMesh(const std::shared_ptr<Mesh>& mesh,const std::shared_ptr<Material>& material,glm::mat4 transformation);
	void EndScene();
private:
	Ref(Camera) m_Camera;
	Ref(Environment)m_Environment;
};

