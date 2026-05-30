#pragma once
#include<string>
class Event;
class Layer
{
public:
	Layer(const std::string& name);
	Layer() = default;
	virtual ~Layer();
	std::string GetName() const { return m_Name; }
	virtual void OnEvent(Event& event) { };
	virtual void OnUpdate(float deltaTime) {};
	virtual void OnAttach() {};
	virtual void OnDetach() {};

private:
	std::string m_Name;
};

