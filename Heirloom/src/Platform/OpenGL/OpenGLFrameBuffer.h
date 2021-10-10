// Author: Milan Dierick
// Created: 28/06/2021 2:54 AM
// Solution: HeirloomEngine

#pragma once

#include "Heirloom/Renderer/Framebuffer.h"

namespace Heirloom
{
	class OpenGLFramebuffer final : public Framebuffer
	{
	public:
		explicit OpenGLFramebuffer(const FramebufferSpecification& spec);
		~OpenGLFramebuffer() override;

		void Invalidate();

		void Bind() override;
		void Unbind() override;

		void Resize(uint32_t width, uint32_t height) override;

		uint32_t GetColorAttachmentRendererID() const override;
		const FramebufferSpecification& GetSpecification() const override;

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FramebufferSpecification m_Specification;
	};
}
