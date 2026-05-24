#include "pch.h"
#include "Application.h"
#include"LayerStack.h"
#include"Layer.h"
#include"Window.h"
#include"Event.h"
#include<GLFW/glfw3.h>
Application::Application()
	:m_Running(0)
{
	m_LayerStack = std::make_unique<LayerStack>();
	m_Window = new Window;
	if (!Application::s_Application)
	{
		printf("s_Application has already exist!\n");
		__debugbreak;
	}
	Application::s_Application = this;


}

Application::~Application()
{
	delete m_Window;
}

void Application::OnEvent(Event& event)
{
	for (auto it = m_LayerStack->End();it != m_LayerStack->Begin();)
	{
		(*--it)->OnEvent(event);
		event.Handled == true;
	}
}

void Application::OnUpdate()
{
	for (auto it = m_LayerStack->Begin();it != m_LayerStack->End();)
	{
		(*it++)->OnUpdate();
	}
}

void Application::PushOverLayer(Layer* overlayer)
{
	m_LayerStack->PushOverLayer(overlayer);
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack->PushLayer(layer);
}

void Application::PopOverLayer(Layer* overlayer)
{
	m_LayerStack->PopOverLayer(overlayer);
}

void Application::PopLayer(Layer* layer)
{
	m_LayerStack->PopLayer(layer);
}

void Application::Run()
{
	while (m_Running)
	{
		OnUpdate();
	}
}
