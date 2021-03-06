﻿// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Layer.h"

namespace Heirloom
{
	/**
	 * \brief Manages the different layers
	 */
	class HL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		LayerStack(const LayerStack& other)                = delete;
		LayerStack(LayerStack&& other) noexcept            = delete;
		LayerStack& operator=(const LayerStack& other)     = delete;
		LayerStack& operator=(LayerStack&& other) noexcept = delete;

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		// ReSharper disable CppInconsistentNaming
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::const_iterator cbegin() const { return m_Layers.cbegin(); }
		std::vector<Layer*>::const_iterator cend() const { return m_Layers.cend(); }
		// ReSharper restore CppInconsistentNaming

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex;
	};
}
