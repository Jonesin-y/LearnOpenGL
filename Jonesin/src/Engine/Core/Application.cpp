#include "pch.h"
#include"Core.h"
#include "Application.h"
#include "input.h"
#include"LayerStack.h"
#include"Layer.h"
#include"Window.h"
#include"Event.h"
#include"WindowEvent.h"
#include<GLFW/glfw3.h>
	Application* Application::s_Application = nullptr;
	Application::Application()
	:m_Running(1),m_deltaTime(0.0f)
	{
		m_LayerStack = std::make_unique<LayerStack>();
		m_Window = std::make_unique<Window>(WindowProps());
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
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowCloseEvent));
		for (auto it = m_LayerStack->End();it != m_LayerStack->Begin();)
		{
			(*--it)->OnEvent(event);
		}
	}

	void Application::OnWindowCloseEvent(WindowCloseEvent& event)
	{
		m_Running = false;
		event.Handled = true;
	}

	void Application::OnUpdate()
	{
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) m_Running = false;
		for (auto it = m_LayerStack->Begin();it != m_LayerStack->End();)
		{
			(*it++)->OnUpdate(m_deltaTime);
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
			m_currentFrame = glfwGetTime();
			m_deltaTime = (m_deltaTime == 0.0f ? 1.0f / 144.0f : m_currentFrame - m_lastFrame);
			m_lastFrame = m_currentFrame;
			//OnEvent will work when GLFWwindow generate event
			m_Window->OnUpdate();
			OnUpdate();
			glfwSwapBuffers(Application::Get()->GetWindow().GetNativeWindow());
		}
	}
