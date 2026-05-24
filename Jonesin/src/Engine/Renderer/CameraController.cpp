#include "pch.h"
#include "CameraController.h"
#include"Application.h"
#include"Input.h"
#include"Camera.h"
#include<GLFW/glfw3.h>

CameraController::CameraController(Camera camera,float deltatime):
m_Camera(camera),m_DeltaTime(deltatime)
{

}

CameraController::~CameraController()
{

}

void CameraController::OnUpdate()
{
	if (Input::IsKeyPressed(GLFW_KEY_S))				m_Camera.ProcessKeyboard(BACKWARD, m_DeltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_W))				m_Camera.ProcessKeyboard(FORWARD, m_DeltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_A))				m_Camera.ProcessKeyboard(LEFT, m_DeltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_D))				m_Camera.ProcessKeyboard(RIGHT, m_DeltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_SPACE))			m_Camera.ProcessKeyboard(UP, m_DeltaTime);
	if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))		m_Camera.ProcessKeyboard(DOWN, m_DeltaTime);
}

void CameraController::OnScrolled()
{

}
