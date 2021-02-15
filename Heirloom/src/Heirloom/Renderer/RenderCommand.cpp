#include "hlpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

Heirloom::RendererAPI* Heirloom::RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

void Heirloom::RenderCommand::SetClearColor(const glm::vec4& color)
{
	s_RendererAPI->SetClearColor(color);
}

void Heirloom::RenderCommand::Clear()
{
	s_RendererAPI->Clear();
}

void Heirloom::RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
	s_RendererAPI->DrawIndexed(vertexArray);
}

