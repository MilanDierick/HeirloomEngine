// Author: Milan Dierick
// Created: 04/03/2021 10:30 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom.h"

namespace Heirloom
{
	class EditorLayer final : public Layer
	{
	public:
		[[nodiscard]] EditorLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(Timestep ts) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		OrthographicCameraController m_CameraController;

		Ref<Texture2D> m_BackgroundTexture;
		Ref<Texture2D> m_Logo;

		Ref<Framebuffer> m_Framebuffer;

		glm::vec2 m_ViewportSize = {0.0f, 0.0f};

		glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
	};
}
