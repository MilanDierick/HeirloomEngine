// Author: Milan Dierick
// Created: 04/03/2021 10:30 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom.h"

class Sandbox2D final : public Heirloom::Layer
{
public:
	[[nodiscard]] Sandbox2D();
	
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Heirloom::Timestep ts) override;
	void OnImGuiRender() override;

private:
	Heirloom::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
