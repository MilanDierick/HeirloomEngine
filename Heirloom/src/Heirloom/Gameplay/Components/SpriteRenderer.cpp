//
// Created by developer on 09/12/2021.
//

#include "SpriteRenderer.h"

Heirloom::SpriteRenderer::SpriteRenderer()
{
	// TODO: This ID should be unique and gotten from some static class that distributes ID's
}

Heirloom::Sprite& Heirloom::SpriteRenderer::GetSprite()
{
	return m_Sprite;
}

void Heirloom::SpriteRenderer::SetSprite(const Sprite& sprite)
{
	m_Sprite = sprite;
}

void Heirloom::SpriteRenderer::Update(Timestep)
{
}

void Heirloom::SpriteRenderer::Render() const
{
	// m_Texture->Bind();
	// Heirloom::Renderer::Submit(m_Texture);
}

void Heirloom::SpriteRenderer::LoadTextureFromPath(const std::string/* path*/)
{
	// m_Texture = Texture2D::Create(path);
}