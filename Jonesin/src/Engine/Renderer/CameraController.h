#pragma once
#include"Camera.h"
class Camera;
class GLFWwindow;
class CameraController
{
public:
	CameraController(Camera camera);
	~CameraController();
	void OnUpdate();
	void OnScrolled();
	
private:
	Camera m_Camera;

};

