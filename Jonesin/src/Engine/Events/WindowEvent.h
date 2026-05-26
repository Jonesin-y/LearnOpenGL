#pragma once
#include"Event.h"
#include<sstream>
class  WindowResizeEvent :public Event
{
public:
	EVENT_CLASS_TYPE(WindowResized);
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
public:
	WindowResizeEvent(int Width, int Height)
		:m_Width(Width), m_Height(Height) {
	}
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}
private:
	int m_Width, m_Height;
};
class  WindowFocusEvent :public Event
{
public:
	WindowFocusEvent() {};
	EVENT_CLASS_TYPE(WindowFocus);
	EVENT_CLASS_CATEGORY(EventCategoryApplication);
};
class  WindowLostFocusEvent :public Event
{
public:
	WindowLostFocusEvent() {};
	EVENT_CLASS_TYPE(WindowLostFocus);
	EVENT_CLASS_CATEGORY(EventCategoryApplication);
};
class  WindowMovedEvent :public Event
{
public:
	WindowMovedEvent(int xPos,int yPos):
		m_xPos(xPos),m_yPos(yPos)
	{}
	EVENT_CLASS_TYPE(WindowMoved);
	EVENT_CLASS_CATEGORY(EventCategoryApplication);
	inline int GetWindowXpos() { return m_xPos; }
	inline int GetWindowYpos() { return m_yPos; }
	virtual std::string ToString()const override 
	{
		std::stringstream ss;
		ss << "WindowMovedEvent:" << m_xPos << "," << m_yPos;
		return ss.str();
	}
private:
	int m_xPos, m_yPos;
};
class  WindowCloseEvent :public Event
{
public:
	WindowCloseEvent() {};
	EVENT_CLASS_TYPE(WindowClosed);
	EVENT_CLASS_CATEGORY(EventCategoryApplication);
};
class  AppTickEvent :public Event
{
public:
	AppTickEvent() {};
	EVENT_CLASS_TYPE(AppTick);
	EVENT_CLASS_CATEGORY(EventCategoryApplication);
};
class  AppUpdateEvent :public Event
{
public:
	AppUpdateEvent() {};
	EVENT_CLASS_TYPE(AppUpdate);
	EVENT_CLASS_CATEGORY(EventCategoryApplication);
};
class  AppRenderEvent :public Event
{
public:
	AppRenderEvent() {};
	EVENT_CLASS_TYPE(AppRender);
	EVENT_CLASS_CATEGORY(EventCategoryApplication);
};
