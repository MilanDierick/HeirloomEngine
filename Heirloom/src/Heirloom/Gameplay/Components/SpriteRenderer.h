#pragma once
#include "Component.h"

#include "Heirloom/Renderer/Texture.h"

namespace Heirloom
{
	class SpriteRenderer final : public Component
	{
	public:
		SpriteRenderer()           = default;
		~SpriteRenderer() override = default;

		SpriteRenderer(const SpriteRenderer& other)                = delete;
		SpriteRenderer(SpriteRenderer&& other) noexcept            = delete;
		SpriteRenderer& operator=(const SpriteRenderer& other)     = delete;
		SpriteRenderer& operator=(SpriteRenderer&& other) noexcept = delete;

		void Update(Timestep ts) override;
		void Render() const override;

	private:
		Scope<Texture2D> m_Texture;
	};
}
