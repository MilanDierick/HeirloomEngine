#include "hlpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

Heirloom::Scope<Heirloom::RendererAPI> Heirloom::RenderCommand::s_RendererAPI = Heirloom::CreateScope<OpenGLRendererAPI
>();

void Heirloom::RenderCommand::Init()
{
	HL_PROFILE_FUNCTION()

	s_RendererAPI->Init();
}

void Heirloom::RenderCommand::SetClearColor(const glm::vec4& color)
{
	HL_PROFILE_FUNCTION()

	s_RendererAPI->SetClearColor(color);
}

void Heirloom::RenderCommand::Clear()
{
	HL_PROFILE_FUNCTION()

	s_RendererAPI->Clear();
}

void Heirloom::RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
	HL_PROFILE_FUNCTION()

	s_RendererAPI->DrawIndexed(vertexArray);
}

void Heirloom::RenderCommand::SetViewport(const uint32_t x,
										  const uint32_t y,
										  const uint32_t width,
										  const uint32_t height)
{
	HL_PROFILE_FUNCTION()

	s_RendererAPI->SetViewport(x, y, width, height);
}
