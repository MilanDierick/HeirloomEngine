// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Component.h"

#include "Heirloom/Renderer/Texture.h"

namespace Heirloom
{
	class SpriteRenderer final : public Component
	{
	public:
		explicit SpriteRenderer();
		~SpriteRenderer() override = default;

		SpriteRenderer(const SpriteRenderer& other)                = delete;
		SpriteRenderer(SpriteRenderer&& other) noexcept            = delete;
		SpriteRenderer& operator=(const SpriteRenderer& other)     = delete;
		SpriteRenderer& operator=(SpriteRenderer&& other) noexcept = delete;

		void Update(Timestep ts) override;
		void Render() const override;

		void LoadTextureFromPath(std::string path);

	private:
		Ref<Texture2D> m_Texture;
	};
}
