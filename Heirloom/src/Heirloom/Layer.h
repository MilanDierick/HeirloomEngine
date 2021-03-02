// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Core/Timestep.h"
#include "Events/Event.h"
#include "Gameplay/GameObject.h"

namespace Heirloom
{
	class HL_API Layer
	{
	public:
		explicit Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = default;

		Layer(const Layer& other)                = delete;
		Layer(Layer&& other) noexcept            = delete;
		Layer& operator=(const Layer& other)     = delete;
		Layer& operator=(Layer&& other) noexcept = delete;
		
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnImGuiRender() = 0;
		virtual void OnEvent(Event& event) = 0;

		const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
		std::vector<GameObject> m_GameObjects;
	};
}
