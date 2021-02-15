#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Heirloom
{
	class RendererAPI
	{
	public:
		RendererAPI() = default;
		virtual ~RendererAPI() = default;

		RendererAPI(const RendererAPI& other) = delete;
		RendererAPI(RendererAPI&& other) noexcept = delete;
		RendererAPI& operator=(const RendererAPI& other) = delete;
		RendererAPI& operator=(RendererAPI&& other) noexcept = delete;

		enum class API
		{
			None = 0,
            OpenGL = 1
        };

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return s_API; }
		
	private:
		static API s_API;
	};
}