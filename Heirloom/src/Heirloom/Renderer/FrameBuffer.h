//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_FRAMEBUFFER_H
#define HEIRLOOM_FRAMEBUFFER_H

#include "Heirloom/Core/Core.h"

namespace Heirloom
{
	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}

#endif //HEIRLOOM_FRAMEBUFFER_H
