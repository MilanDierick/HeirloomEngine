// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once

namespace Heirloom
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	protected:
		GraphicsContext() = default;
		~GraphicsContext() = default;

		GraphicsContext(const GraphicsContext& other)                = delete;
		GraphicsContext(GraphicsContext&& other) noexcept            = delete;
		GraphicsContext& operator=(const GraphicsContext& other)     = delete;
		GraphicsContext& operator=(GraphicsContext&& other) noexcept = delete;
	};
}
