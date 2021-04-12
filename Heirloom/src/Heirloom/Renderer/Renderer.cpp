#include "hlpch.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

Heirloom::Scope<Heirloom::Renderer::SceneData> Heirloom::Renderer::s_SceneData = Heirloom::CreateScope<SceneData>();

void Heirloom::Renderer::Init()
{
	HL_PROFILE_FUNCTION()

	RenderCommand::Init();
	Renderer2D::Init();
}

void Heirloom::Renderer::OnWindowResize(const uint32_t width, const uint32_t height)
{
	RenderCommand::SetViewport(0, 0, width, height);
}

void Heirloom::Renderer::BeginScene(OrthographicCamera& camera)
{
	s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Heirloom::Renderer::EndScene()
{
}

void Heirloom::Renderer::Submit(const Ref<Shader>& shader,
								const Ref<VertexArray>& vertexArray,
								const glm::mat4& transform)
{
	HL_PROFILE_FUNCTION()

	shader->Bind();
	std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection",
																	   s_SceneData->ViewProjectionMatrix);
	std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
