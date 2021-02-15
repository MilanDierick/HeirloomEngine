#pragma once
#include "Heirloom/Renderer/VertexArray.h"

namespace Heirloom
{	
	class OpenGLVertexArray final : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		OpenGLVertexArray(const OpenGLVertexArray& other)                = delete;
		OpenGLVertexArray(OpenGLVertexArray&& other) noexcept            = delete;
		OpenGLVertexArray& operator=(const OpenGLVertexArray& other)     = delete;
		OpenGLVertexArray& operator=(OpenGLVertexArray&& other) noexcept = delete;
		
		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		// ReSharper disable once CppConstValueFunctionReturnType
		const Ref<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }
	
	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}