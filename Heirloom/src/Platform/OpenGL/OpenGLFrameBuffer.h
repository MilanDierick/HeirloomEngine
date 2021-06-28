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

		uint32_t GetColorAttachmentRendererID() const override;
		const FramebufferSpecification& GetSpecification() const override;

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FramebufferSpecification m_Specification;
	};
}
