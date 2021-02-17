#pragma once
#include "Heirloom/Renderer/RendererAPI.h"

namespace Heirloom
{
	class OpenGLRendererAPI final : public RendererAPI
	{
	public:
		void Init() override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		
		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}
