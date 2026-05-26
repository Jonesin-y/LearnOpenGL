#pragma once
#include"Event.h"
#include<sstream>
class KeyEvent :public Event
{
public:
	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
public:
	inline int GetKeyCode() const { return m_KeyCode; }
protected:
	int m_KeyCode;
	KeyEvent(int KeyCode) :
		m_KeyCode(KeyCode) {
	}
};
class KeyPressedEvent :public KeyEvent
{
public:
	EVENT_CLASS_TYPE(KeyPressed);
public:
	KeyPressedEvent(int keyCode, int repeatCount)
		: KeyEvent(keyCode), m_RepeatCount(repeatCount) {
	}
	inline int GetRepeatCount() const { return m_RepeatCount; }
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << "( " << m_RepeatCount << " repeats)";
		return ss.str();
	}
private:
	int m_RepeatCount;
};
class KeyReleasedEvent :public KeyEvent
{
public:
	EVENT_CLASS_TYPE(KeyReleased);
public:
	KeyReleasedEvent(int KeyCode) :
		KeyEvent(KeyCode) {
	}
	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}

};

