#include "hlpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

Heirloom::Ref<Heirloom::VertexBuffer> Heirloom::VertexBuffer::Create(float* vertices, const uint32_t size)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None:
		HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
	}

	HL_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Heirloom::Ref<Heirloom::IndexBuffer> Heirloom::IndexBuffer::Create(uint32_t* indices, const uint32_t size)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None:
		HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, size);
	}

	HL_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
