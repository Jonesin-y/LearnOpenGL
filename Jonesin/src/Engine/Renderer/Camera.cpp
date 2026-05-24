#include "pch.h"
#include "Camera.h"

//glm::mat4 MyLookAt(glm::vec3 Pos, glm::vec3 target, glm::vec3 Up)
//{
//	glm::vec3 z = glm::normalize(Pos - target);
//	glm::vec3 x = glm::normalize(glm::cross(Up,z));
//	glm::vec3 y = glm::normalize(glm::cross(z, x));
//	glm::mat4 Rotation = glm::mat4(1.0f);
//	Rotation[0][0] = x.x;
//	Rotation[1][0] = x.y;
//	Rotation[2][0] = x.z;
//	Rotation[0][1] = y.x;
//	Rotation[1][1] = y.y;
//	Rotation[2][1] = y.z;
//	Rotation[0][2] = z.x;
//	Rotation[1][2] = z.y;
//	Rotation[2][2] = z.z;
//	glm::mat4 translation = glm::translate(glm::mat4(1.0f), -Pos);
//	glm::mat4 Result =  Rotation * translation;
//
//
//
//	return Result;
//}
Camera::Camera(glm::vec3 position, glm::vec3 up, float pitch , float yaw):
	Position(position),
	Up(up),
	WorldUp(up),
	Pitch(pitch),
	Yaw(yaw),
	Sensitivity(DEFAULT_SENSITYVITY),
	Zoom(DEFAULT_ZOOM),
	Speed(DEFAULT_SPEED)
{
	updateCameraVectors();
}

Camera::~Camera()
{

}


void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	updateCameraVectors();
	switch (direction)
	{
	case FORWARD:
		Position += Front * Speed * deltaTime;
		break;
	case BACKWARD:
		Position -= Front * Speed * deltaTime;
		break;
	case LEFT:
		Position -= Right * Speed * deltaTime;
		break;
	case RIGHT:
		Position += Right * Speed * deltaTime;
		break;
	case UP:
		Position += WorldUp * Speed * deltaTime;
		break;
	case DOWN:
		Position -= WorldUp * Speed * deltaTime;
		break;
	default:
		break;
	}
}

void Camera::ProcessMouseMovement(double xOffset, double yOffset)
{
	Pitch += yOffset * Sensitivity;
	if (Pitch >= 89.0f) Pitch = 89.0f;
	if (Pitch <= -89.0f) Pitch = -89.0f;
	Yaw   += xOffset * Sensitivity;
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(double xOffset, double yOffset)
{

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}



void Camera::updateCameraVectors()
{
	Right = glm::normalize(glm::cross(Front,Up));
	Front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Front.y = sin(glm::radians(Pitch));
	Front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	Front = glm::normalize(Front);
}
