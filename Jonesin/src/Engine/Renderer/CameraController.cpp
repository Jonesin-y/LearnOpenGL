#include "pch.h"
#include "CameraController.h"
#include"Application.h"
#include"Input.h"
#include"Camera.h"
#include"Event.h"
#include"KeyEvent.h"
#include"MouseEvent.h"
#include<GLFW/glfw3.h>

CameraController::CameraController(Camera& camera):
m_Camera(camera),m_firstMouse(true)
{

}

CameraController::~CameraController()
{

}

void CameraController::OnUpdate(float deltaTime)
{
	if (Input::IsKeyPressed(GLFW_KEY_S))				m_Camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_W))				m_Camera.ProcessKeyboard(FORWARD, deltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_A))				m_Camera.ProcessKeyboard(LEFT, deltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_D))				m_Camera.ProcessKeyboard(RIGHT, deltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_SPACE))			m_Camera.ProcessKeyboard(UP, deltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))		m_Camera.ProcessKeyboard(DOWN, deltaTime);
}

bool CameraController::OnScrolled(const MouseScrolledEvent& event)
{
	return true;
}

bool CameraController::OnMouseMoved(const MouseMovedEvent& event)
{
	m_firstMouse = true;
	if (m_firstMouse)
	{
		m_lastX = event.GetMouseX();
		m_lastY = event.GetMouseY();
		m_firstMouse = false;
	}
	static double xOffset = 0.0f;
	static double yOffset = 0.0f;
	xOffset = event.GetMouseX() - m_lastX;
	yOffset = m_lastY - event.GetMouseY();
	m_lastX = event.GetMouseX();
	m_lastY = event.GetMouseY();
	m_Camera.ProcessMouseMovement(xOffset, yOffset);
	return true;
}

void CameraController::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(CameraController::OnMouseMoved));
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(CameraController::OnScrolled));
}
