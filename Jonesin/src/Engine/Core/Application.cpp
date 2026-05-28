#include "pch.h"
#include"Core.h"
#include "Application.h"
#include"LayerStack.h"
#include"Layer.h"
#include"Window.h"
#include"Event.h"
#include<GLFW/glfw3.h>
	Application* Application::s_Application = nullptr;
	Application::Application()
		:m_Running(0)
	{
		m_LayerStack = std::make_unique<LayerStack>();
		m_Window = std::make_unique<Window>();
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		if (Application::s_Application)
		{
			printf("s_Application has already exist!\n");
			__debugbreak();
		}
		Application::s_Application = this;


	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& event)
	{
		for (auto it = m_LayerStack->End();it != m_LayerStack->Begin();)
		{
			(*--it)->OnEvent(event);
			event.Handled = true;
		}
	}

	void Application::OnUpdate()
	{
		for (auto it = m_LayerStack->Begin();it != m_LayerStack->End();)
		{
			(*it++)->OnUpdate();
		}
	}

	void Application::PushOverLayer(Ref(Layer) overlayer)
	{
		m_LayerStack->PushOverLayer(overlayer);
	}

	void Application::PushLayer(Ref(Layer) layer)
	{
		m_LayerStack->PushLayer(layer);
	}

	void Application::PopOverLayer(Ref(Layer) overlayer)
	{
		m_LayerStack->PopOverLayer(overlayer);
	}

	void Application::PopLayer(Ref(Layer) layer)
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
