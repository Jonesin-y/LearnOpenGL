#include "pch.h"
#include "CameraController.h"
#include "Glad/glad.h"
#include"Camera.h"

CameraController::CameraController(Camera camera):
m_Camera(camera)
{

}

CameraController::~CameraController()
{

}

void CameraController::OnUpdate()
{
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)				myCamera.ProcessKeyboard(BACKWARD, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)				myCamera.ProcessKeyboard(FORWARD, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)				myCamera.ProcessKeyboard(LEFT, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)				myCamera.ProcessKeyboard(RIGHT, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)			myCamera.ProcessKeyboard(UP, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)	myCamera.ProcessKeyboard(DOWN, deltaTime);
}

void CameraController::OnScrolled()
{

}
