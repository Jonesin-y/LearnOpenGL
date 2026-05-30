#pragma once
#include"Core.h"
#include"Camera.h"
class Event;
class MouseScrolledEvent;
class MouseMovedEvent;
class CameraController
{
public:
	CameraController(Ref(Camera) camera);
	~CameraController();
	void OnUpdate(float deltaTime);
	void OnScrolled(MouseScrolledEvent& event);
	void OnMouseMoved(MouseMovedEvent& event);
	void OnEvent(Event& event);
	
	
private:
	Ref(Camera) m_Camera;

	//deal with Mouse Moved event,this may be let you feel wired,so do i,it will be optimized in the future;
	bool m_firstMouse;
	float m_lastX, m_lastY;
	float m_xOffset = 0.0f;
	float m_yOffset = 0.0f;

};

