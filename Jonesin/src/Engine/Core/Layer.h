#pragma once
#include<string>
class Event;
class Layer
{
public:
	Layer(const std::string& name);
	Layer() = default;
	~Layer();
	std::unique_ptr<Layer>Create(const std::string& name) { return std::make_unique<Layer>(name); }
	std::string GetName() const { return m_Name; }
	virtual void OnEvent(const Event& event) {};
	virtual bool OnUpdate(const Event& event) {};
	virtual void OnAttach() {};
	virtual void OnDetach() {};

private:
	std::string m_Name;
};

