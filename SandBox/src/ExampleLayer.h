#pragma once
#include"Jonesin.h"
#include <memory>
#include<unordered_map>
class ExampleLayer :public Layer
{
public:
	ExampleLayer();;
	~ExampleLayer() = default;
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(float deltatime);
	virtual void OnEvent(Event& event);
	void OnKeyPressedEvent(KeyPressedEvent& event);
private:
	//ECS system will be done in the future
	std::vector<glm::mat4>m_Transforms;
	float m_rotateSpeed = 125.0f;

	Ref(Renderer3D)m_Renderer3D;

	//Scene and SceneManager will be completed in the future
	//std::vector<Ref(Scene)>m_Scenes;

	Ref(ShaderLibrary)m_ShaderLibrary;
	std::unordered_map<std::string, Ref(Mesh)>m_Meshs;
	std::unordered_map<std::string, Ref(Camera)>m_Cameras;
	std::unordered_map<std::string, Ref(CameraController)>m_CameraControllers;

	//Asset manager will be completed in the future
	std::unordered_map<std::string, Ref(Material)>m_Materials;
	std::unordered_map<std::string, Ref(Texture2D)>m_Texture2Ds;


};
