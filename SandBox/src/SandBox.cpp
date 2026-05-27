#include"Jonesin.h"
#include<memory>
class ExampleLayer :public Layer
{
public:
	ExampleLayer()
	{

	};
	~ExampleLayer() = default;
	virtual void OnAttach()
	{

	}
	virtual void OnDetach()
	{
	}
	virtual void OnUpdate()
	{
	}
	virtual void OnEvent(Event& event)
	{

	}
private:
	Shader shader
};
class SandBox : public Application
{
public:
	SandBox() 
	{
		m_LayerStack->PushLayer(std::make_shared<ExampleLayer>());
	}

};
Application* CreateApplication() { return new SandBox; }