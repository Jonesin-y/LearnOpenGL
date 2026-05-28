#pragma once
#include"Camera.h"
class Event;
class MouseScrolledEvent;
class MouseMovedEvent;
class CameraController
{
public:
	CameraController(Camera& camera);
	~CameraController();
	void OnUpdate(float deltaTime);
	bool OnScrolled(const MouseScrolledEvent& event);
	bool OnMouseMoved(const MouseMovedEvent& event);
	void OnEvent(Event& event);
	
	
private:
	Camera m_Camera;

	//deal with Mouse Moved event,this may be let you feel wired,so do i,it will be optimized in the future;
	bool m_firstMouse;
	float m_lastX, m_lastY;

};

