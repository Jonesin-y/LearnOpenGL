#include"Jonesin.h"
class ExampleLayer :public Layer
{
public:
	ExampleLayer() = default;
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
};
class SandBox : public Application
{
public:
	SandBox() {};

};
Application* CreateApplication() { return new SandBox; }