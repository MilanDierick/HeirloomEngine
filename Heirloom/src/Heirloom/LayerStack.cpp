#include "hlpch.h"
#include "LayerStack.h"

Heirloom::LayerStack::LayerStack(): m_LayerInsertIndex(0) {}

Heirloom::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
		delete layer;
}

void Heirloom::LayerStack::PushLayer(Layer* layer)
{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		++m_LayerInsertIndex;
}

void Heirloom::LayerStack::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
}

void Heirloom::LayerStack::PopLayer(Layer* layer)
{
	const auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if (it != m_Layers.end())
	{
		m_Layers.erase(it);
		--m_LayerInsertIndex;
	}
}

void Heirloom::LayerStack::PopOverlay(Layer* overlay)
{
	const auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end())
		m_Layers.erase(it);
}
