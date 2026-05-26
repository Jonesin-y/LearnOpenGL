#pragma once
#include<vector>
class Layer;
class Event;
class LayerStack
{
public:
	LayerStack();
	~LayerStack();
	inline std::vector<Layer*>::iterator Begin() { return m_Layers.begin(); }
	inline std::vector<Layer*>::iterator End() { return m_Layers.end(); }
	void PopOverLayer(Layer* overlayer);
	void PopLayer(Layer* layer);
	void PushOverLayer(Layer* overlayer);
	void PushLayer(Layer* layer);
public:
	int m_InsertIndex;
	std::vector<Layer*>m_Layers;
};

