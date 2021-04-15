#include "hlpch.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

void Heirloom::OpenGLRendererAPI::Init()
{
	HL_PROFILE_FUNCTION()

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void Heirloom::OpenGLRendererAPI::SetViewport(const uint32_t x,
											  const uint32_t y,
											  const uint32_t width,
											  const uint32_t height)
{
	glViewport(x, y, width, height);
}

void Heirloom::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Heirloom::OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Heirloom::OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t indexCount)
{
	HL_PROFILE_FUNCTION()

	const uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}
