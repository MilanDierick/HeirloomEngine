//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_SPRITERENDERER_H
#define HEIRLOOM_SPRITERENDERER_H

#include "Component.h"
#include "Heirloom/Renderer/Sprite.h"

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

		[[nodiscard]] Sprite& GetSprite();
		void SetSprite(const Sprite& sprite);

		void Update(Timestep ts) override;
		void Render() const override;

		void LoadTextureFromPath(std::string path);

	private:
		Sprite m_Sprite;
	};
}

#endif //HEIRLOOM_SPRITERENDERER_H
