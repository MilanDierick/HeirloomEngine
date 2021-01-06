#pragma once

namespace Heirloom
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	protected:
		~GraphicsContext() = default;
	};
}
