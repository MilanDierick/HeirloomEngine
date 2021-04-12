// Author: Milan Dierick
// Created: 12/04/2021 3:55 AM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom.h"

class SandboxScene2D final : public Heirloom::Scene
{
public:
	explicit SandboxScene2D(const std::string& sceneName);

	void OnLoad() override;
	void OnUnload() override;
	void OnUpdate() override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	Heirloom::OrthographicCameraController m_CameraController;

	Heirloom::Sprite m_BackgroundSprite;

	Heirloom::Ref<Heirloom::Texture2D> m_BackgroundTexture;
	Heirloom::Ref<Heirloom::Texture2D> m_Logo;

	glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
