#include "hlpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

Heirloom::Ref<Heirloom::VertexArray> Heirloom::VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None:
			HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		return nullptr;
		case RendererAPI::API::OpenGL:
			return Heirloom::CreateRef<OpenGLVertexArray>();
	}

	HL_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
