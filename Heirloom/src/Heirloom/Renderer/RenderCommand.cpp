#include "hlpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

Heirloom::Scope<Heirloom::RendererAPI> Heirloom::RenderCommand::s_RendererAPI = Heirloom::CreateScope<Heirloom::OpenGLRendererAPI>();

void Heirloom::RenderCommand::Init()
{
	s_RendererAPI->Init();
}

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

void Heirloom::RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	s_RendererAPI->SetViewport(x, y, width, height);
}

