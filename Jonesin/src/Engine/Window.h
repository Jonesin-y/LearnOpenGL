#pragma once
class Event;
class GLFWwindow;
struct WindowProps
{
	float width;
	float height;
	std::string title;
};
class Window
{
public:
	Window(const WindowProps& prop);
	~Window();
	bool Init(const WindowProps& prop);
	void OnUpdate();
	void SetVSync(bool VSync);
	bool IsVSync();
	void SetEventCallback(std::function<void(Event&)> callback);
	float GetWidth();
	float GetHeight();

private:
	struct WindowData
	{
		float width;
		float height;
		bool isVSync;
		std::string title;
		std::function<void(Event&)> EventCallback;
	};
	GLFWwindow* m_Window;
	WindowData m_Data;
};

