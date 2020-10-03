#pragma once
#include "Layer.h"

namespace Heirloom
{
	class HL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator Begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator End() { return m_Layers.end(); }
		std::vector<Layer*>::const_iterator CBegin() const { return m_Layers.cbegin(); }
		std::vector<Layer*>::const_iterator CEnd() const { return m_Layers.cend(); }
		private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}
