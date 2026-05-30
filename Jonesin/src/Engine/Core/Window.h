#pragma once
#include"Event.h"
struct GLFWwindow;
struct WindowProps
{
	std::string title;
	int width;
	int height;
	WindowProps(const std::string& Title = "MyOpenGL",
		float Width = 960.0f,
		float Height = 640.0f) :
		title(Title), width(Width), height(Height)
	{
	}
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
	inline GLFWwindow* GetNativeWindow() { return m_Window; }
	float GetWidth();
	float GetHeight();

private:
	struct WindowData
	{
		int width;
		int height;
		bool isVSync;
		std::string title;
		std::function<void(Event&)> EventCallback;
	};
	GLFWwindow* m_Window;
	WindowData m_Data;
};

