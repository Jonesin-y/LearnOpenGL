#include "pch.h"
#include"Event.h"
#include "LayerStack.h"
#include"Layer.h"

LayerStack::LayerStack()
	:m_InsertIndex(0)
{

}

LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		delete layer;
	}
}

void LayerStack::PopOverLayer(Layer* overlayer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);
	if (it != m_Layers.end()) { 
		m_Layers.erase(it);
		overlayer->OnUpdate();
		return;
	}
	std::cout << "LayerStack doesn't exist this Layer!" << std::endl;
}

void LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if (it != m_Layers.end()) {
		m_Layers.erase(it);
		layer->OnDetach();
		m_InsertIndex--;
		return;
	}
	std::cout << "LayerStack doesn't exist this Layer!" << std::endl;

}

void LayerStack::PushOverLayer(Layer* overlayer)
{
	m_Layers.emplace_back(overlayer);
}

void LayerStack::PushLayer(Layer* layer)
{
	m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
	layer->OnAttach();
	m_InsertIndex++;
}
