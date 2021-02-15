#pragma once
#include "Component.h"

#include "Heirloom/Renderer/Texture.h"

namespace Heirloom
{
	class SpriteRenderer final : public Component
	{
	public:
		explicit SpriteRenderer(uint32_t id);
		virtual ~SpriteRenderer() = default;

		SpriteRenderer(const SpriteRenderer& other)                = delete;
		SpriteRenderer(SpriteRenderer&& other) noexcept            = delete;
		SpriteRenderer& operator=(const SpriteRenderer& other)     = delete;
		SpriteRenderer& operator=(SpriteRenderer&& other) noexcept = delete;

		uint32_t GetID() const override { return m_ID; }
		
		void Update(Timestep ts) override;
		void Render() const override;

		void LoadTextureFromPath(std::string path);
	
	private:
		uint32_t m_ID;
		Ref<Texture2D> m_Texture;
	};
}
