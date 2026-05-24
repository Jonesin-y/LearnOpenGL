#pragma once
class Window;
class Event;
class LayerStack;
class Layer;
class Application
{
public:
	Application();
	virtual ~Application();
	inline Window* GetWindow() { return m_Window; }
	inline static Application* Get() { return s_Application; }
	void OnEvent(Event& event);
	void OnUpdate();
	void PushOverLayer(Layer* overlayer);
	void PushLayer(Layer* layer);
	void PopOverLayer(Layer* overlayer);
	void PopLayer(Layer* layer);
	void Run();

private:
	//个人项目暂时只考虑window平台，所以就不单独封装Window类了
	bool m_Running;
	std::unique_ptr<LayerStack> m_LayerStack;
	Window* m_Window;
	static Application* s_Application;
	
};

