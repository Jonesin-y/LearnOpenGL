#pragma once
#include"Core.h"
#include"Layer.h"
#include <memory>
class Renderer3D;
class ShaderLibrary;
class Camera;
class CameraController;
class Scene;
class ExampleLayer :public Layer
{
public:
	ExampleLayer();;
	~ExampleLayer() = default;
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate();
	virtual void OnEvent(Event& event);
private:

	//Scene class will be completed in the future
	//std::vector<Ref(Scene)>m_Scenes;

	Ref(ShaderLibrary)m_ShaderLibrary;
	std::vector<Ref(Mesh)> m_Meshs;
	Ref(Camera)m_Camera;
	Ref(CameraController)m_CameraController;
	Ref(Renderer3D)m_Renderer3D;
	
};
