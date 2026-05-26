#pragma once
#include"Event.h"
#include<sstream>
class MouseMovedEvent :public Event
{
public:
	EVENT_CLASS_TYPE(MouseMoved);
	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
public:
	MouseMovedEvent(float MouseX, float MouseY) :
		m_MouseX(MouseX), m_MouseY(MouseY) {
	}
	inline float GetMouseX() const { return m_MouseX; }
	inline float GetMouseY() const { return m_MouseY; }
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

private:
	float m_MouseX, m_MouseY;
};
class MouseScrolledEvent :public Event
{
public:
	EVENT_CLASS_TYPE(MouseScrolled);
	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse);
public:
	MouseScrolledEvent(float ScrolledX, float ScrolledY) :
		m_ScrolledX(ScrolledX), m_ScrolledY(ScrolledY) {
	}
	inline float GetScrolledX() const { return m_ScrolledX; }
	inline float GetScrolledY() const { return m_ScrolledY; }
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << m_ScrolledX << ", " << m_ScrolledY;
		return ss.str();
	}

private:
	float m_ScrolledX, m_ScrolledY;
};
class MouseButtonEvent :public Event
{
public:
	EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput);
public:
	MouseButtonEvent(int buttonCode)
		: m_ButtonCode(buttonCode) {
	}
	inline int GetButtonCode() const { return m_ButtonCode; }
protected:
	int m_ButtonCode;
};
class MouseButtonPressedEvent :public MouseButtonEvent
{
public:
	EVENT_CLASS_TYPE(MousePressed);
public:
	MouseButtonPressedEvent(int buttonCode)
		: MouseButtonEvent(buttonCode) {
	}
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_ButtonCode;
		return ss.str();
	}

};
class MouseButtonReleasedEvent :public MouseButtonEvent
{
public:
	EVENT_CLASS_TYPE(MouseReleased);
public:
	MouseButtonReleasedEvent(int buttonCode) :
		MouseButtonEvent(buttonCode) {
	}
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_ButtonCode;
		return ss.str();
	}
};

