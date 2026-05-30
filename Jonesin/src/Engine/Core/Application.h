#pragma once
#include"Core.h"
#include<memory>
class Window;
class Event;
class WindowCloseEvent;
class LayerStack;
class Layer;
class Application
{
public:
	Application();
	virtual ~Application();
	inline Window& GetWindow() { return *m_Window; }
	inline static Application* Get() { return s_Application; }
	void OnEvent(Event& event);
	void OnWindowCloseEvent(WindowCloseEvent& event);
	void OnUpdate();
	void PushOverLayer(Ref(Layer) overlayer);
	void PushLayer(Ref(Layer) layer);
	void PopOverLayer(Ref(Layer) overlayer);
	void PopLayer(Ref(Layer) layer);
	void Run();

protected:
	bool m_Running;
	//caculate deltaTime
	float m_currentFrame=0.0f;
	float m_lastFrame=0.0f;
	float m_deltaTime;
	std::unique_ptr<LayerStack> m_LayerStack;
	std::unique_ptr<Window> m_Window;
	static Application* s_Application;
	
};
Application* CreateApplication();

