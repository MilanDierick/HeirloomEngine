#include "hlpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

Heirloom::Ref<Heirloom::Texture2D> Heirloom::Texture2D::Create(const std::string& path)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None:
			HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
	}

	HL_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
