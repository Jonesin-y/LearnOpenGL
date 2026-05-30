#pragma once
#include"Core.h"
#include<vector>
class Layer;
class Event;
class LayerStack
{
public:
	LayerStack();
	virtual ~LayerStack();
	inline std::vector<Ref(Layer)>::iterator Begin() { return m_Layers.begin(); }
	inline std::vector<Ref(Layer)>::iterator End() { return m_Layers.end(); }
	void PopOverLayer(Ref(Layer) overlayer);
	void PopLayer(Ref(Layer) layer);
	void PushOverLayer(Ref(Layer) overlayer);
	void PushLayer(Ref(Layer) layer);
public:
	int m_InsertIndex;
	std::vector<Ref(Layer)>m_Layers;
};

