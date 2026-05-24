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
	if (!Init(prop))
	{
		printf("Fail to Create Window!\n");
		__debugbreak;
	}
}

Window::~Window()
{

}

bool Window::Init(const WindowProps& prop)
{
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

		});
	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

		});
	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
		WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);



		});
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
