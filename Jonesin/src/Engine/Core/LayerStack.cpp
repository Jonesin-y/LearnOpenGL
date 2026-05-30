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
}

void LayerStack::PopOverLayer(Ref(Layer) overlayer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);
	if (it != m_Layers.end()) { 
		m_Layers.erase(it);
		overlayer->OnDetach();
		return;
	}
	std::cout << "LayerStack doesn't exist this Layer!" << std::endl;
}

void LayerStack::PopLayer(Ref(Layer) layer)
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

void LayerStack::PushOverLayer(Ref(Layer) overlayer)
{
	m_Layers.emplace_back(overlayer);
}

void LayerStack::PushLayer(Ref(Layer) layer)
{
	m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
	layer->OnAttach();
	m_InsertIndex++;
}
