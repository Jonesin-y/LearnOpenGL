#pragma once
#include"Core.h"
#include<functional>
#include<string>
#define EVENT_CLASS_TYPE(type)		static EventType GetStaticType(){return EventType::type;}\
									virtual EventType GetEventType()const override{return EventType::##type;}\
									virtual std::string GetTypeName()const override{return #type;}
#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategory() const override{return category;}
enum class EventType
{
	NONE,
	WindowClosed,WindowResized,WindowMoved,WindowFocus,WindowLostFocus,
	MousePressed,MouseReleased,MouseMoved,MouseScrolled,
	KeyPressed,KeyReleased,
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
	virtual int GetEventCategory() const { return NONE; }
	virtual EventType GetEventType() const { return EventType::NONE; }
	virtual std::string GetTypeName()const { return ""; }
	virtual std::string ToString() const { return GetTypeName(); }
	bool isInCategory(int category) { return category & GetEventCategory(); }
public:
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
	void Dispatch(EventFn<T> func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			func(static_cast<T&>(m_Event));
		}
	}
private:
	Event& m_Event;
};