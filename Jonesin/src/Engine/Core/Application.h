#pragma once
#include"Core.h"
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
	void PushOverLayer(Ref(Layer) overlayer);
	void PushLayer(Ref(Layer) layer);
	void PopOverLayer(Ref(Layer) overlayer);
	void PopLayer(Ref(Layer) layer);
	void Run();

protected:
	bool m_Running;
	std::unique_ptr<LayerStack> m_LayerStack;
	std::unique_ptr<Window> m_Window;
	static Application* s_Application;
	
};
Application* CreateApplication();

