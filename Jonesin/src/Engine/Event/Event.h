#pragma once
#include"Core.h"
#define EVENT_CLASS_TYPE(type)		static EventType GetStaticType(){return type;}\
									virtual EventType GetEventType()const override{return type;}\
									virtual std::string GetTypeName()const override{return #type;}
#define EVENT_CLASS_CATEGORY(category) virtual EventCategory GetEventCategory() const override{return category;}
enum class EventType
{
	WindowClose,WindowResize,WindowMove,WindowFocus，WindowLostFocus,
	MousePresse,MouseRelease,MouseMove,MosueScrolle,
	KeyPresseEvent,KeyReleaseEvent,
	AppTick,AppUpdate,AppRender
};
enum EventCategory
{
	NONE = 0,
	EventCategoryApplication = BIT(0),
	EventCategoryInput = BIT(1),
	EventCategoryKeyboard = BIT(2),
	EventCategoryMouse = BIT(3),
	EventCategoryMouseButton = BIT(4)
};


class Event
{
	friend class EventDispatcher;
public:
	virtual EventCategory GetEventCategoty() const {}
	virtual EventType GetEventType() const {}
	virtual std::string GetTypeName()const {}
	virtual std::string ToString() const { return GetTypeName(); }
	bool isInCategory(int category) { return category & GetEventCategoty(); }
private:
	bool Handled = false;

};
class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<void(T&)>;
public:
	EventDispatcher(Event& event)
		:m_Event(event){
	}
	template<typename T>
	bool Dispatch(EventFn<T> func)
	{
		if (m_Event.GetEventType == T::GetStaticType())
		{
			return m_Event.Handled = func(*(T*)&m_Event);
		}
	}
private:
	Event& m_Event;
};