// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Core/Layer.h"

namespace Heirloom
{
	// TODO: Start providing custom implementations for some of these ImGui example functions, they are slow!
	class HL_API ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		ImGuiLayer(const ImGuiLayer& other)                = delete;
		ImGuiLayer(ImGuiLayer&& other) noexcept            = delete;
		ImGuiLayer& operator=(const ImGuiLayer& other)     = delete;
		ImGuiLayer& operator=(ImGuiLayer&& other) noexcept = delete;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep) override
		{
		}

		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}
