#pragma once
#include "Heirloom/Renderer/RendererAPI.h"

namespace Heirloom
{
	class OpenGLRendererAPI final : public RendererAPI
	{
	public:
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
