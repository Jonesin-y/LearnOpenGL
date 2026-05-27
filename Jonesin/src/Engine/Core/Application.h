#pragma once
#include<memory>
class Window;
class Event;
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
	void OnUpdate();
	void PushOverLayer(Layer* overlayer);
	void PushLayer(Layer* layer);
	void PopOverLayer(Layer* overlayer);
	void PopLayer(Layer* layer);
	void Run();

protected:
	bool m_Running;
	std::unique_ptr<LayerStack> m_LayerStack;
	std::unique_ptr<Window> m_Window;
	static Application* s_Application;
	
};
Application* CreateApplication();

