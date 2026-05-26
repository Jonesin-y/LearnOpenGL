#include "pch.h"
#include"Event.h"
#include"KeyEvent.h"
#include"MouseEvent.h"
#include"WindowEvent.h"
#include "Window.h"
#include<Glad/glad.h>
#include<GLFW/glfw3.h>

Window::Window(const WindowProps& prop)
{
	m_Data.title = prop.title;
	m_Data.width = prop.width;
	m_Data.height = prop.height;
	if (!Init(prop))
	{
		printf("Fail to Create Window!\n");
		__debugbreak();
	}
	
}

Window::~Window()
{

}

bool Window::Init(const WindowProps& prop = WindowProps())
{
	if (!glfwInit())
		return false;
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return false;
	}
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
		});
	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				{
			case GLFW_PRESS:
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
				}
				{
			case GLFW_RELEASE:
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
				}
			}
		});
	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event(x, y);
			data.EventCallback(event);


		});
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			data.EventCallback(event);

		});
	glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xPos, int yPos) {
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowMovedEvent event(xPos, yPos);

		});
	return true;
}

void Window::OnUpdate()
{

}

void Window::SetVSync(bool VSync)
{
	m_Data.isVSync = VSync;
}

bool Window::IsVSync()
{
	switch (m_Data.isVSync)
	{
	case true:return true;
	case false:return false;
	}
}

void Window::SetEventCallback(std::function<void(Event&)> callback)
{
	m_Data.EventCallback = callback;
}

float Window::GetWidth()
{
	return m_Data.width;
}

float Window::GetHeight()
{
	return m_Data.height;
}
