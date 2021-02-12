#include "hlpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Heirloom/Application.h"
#include "Platform/OpenGL/OpenGLShader.h"

Heirloom::Shader* Heirloom::Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None:
		HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
	}

	HL_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
