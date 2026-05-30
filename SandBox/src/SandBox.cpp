#include"Jonesin.h"
#include"EntryPoint.h"
#include"ExampleLayer.h"
#include<memory>

class SandBox : public Application
{
public:
	SandBox() 
	{
		m_LayerStack->PushLayer(std::make_shared<ExampleLayer>());
	}

};
Application* CreateApplication() { return new SandBox; }