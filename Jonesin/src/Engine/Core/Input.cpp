#include "pch.h"
#include "Input.h"
#include"Application.h"
#include "Window.h"
#include"GLFW/glfw3.h"
bool Input::IsKeyPressed(int KeyCode)
{
	GLFWwindow* window = Application::Get()->GetWindow().GetNativeWindow();
	if (glfwGetKey(window, KeyCode) == GLFW_PRESS) return true;
	return false;
}

bool Input::IsMousePressed(int MouseCode)
{
	GLFWwindow* window = Application::Get()->GetWindow().GetNativeWindow();
	if (glfwGetMouseButton(window,MouseCode) == GLFW_PRESS) return true;
	return false;
}

std::pair<float,float> Input::GetCursorPos()
{
	GLFWwindow* window = Application::Get()->GetWindow().GetNativeWindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return { (float)xpos,(float)ypos};
}

float Input::GetCursorPosX()
{
	auto [x, y] = GetCursorPos();
	return x;
}

float Input::GetCursorPosY()
{
	auto [x, y] = GetCursorPos();
	return y;
}
