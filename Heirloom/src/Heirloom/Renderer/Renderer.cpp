#include "hlpch.h"
#include "Renderer.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

Heirloom::Renderer::SceneData* Heirloom::Renderer::m_SceneData = new SceneData;

void Heirloom::Renderer::Init()
{
	RenderCommand::Init();
}

void Heirloom::Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	RenderCommand::SetViewport(0, 0, width, height);
}

void Heirloom::Renderer::BeginScene(OrthographicCamera& camera)
{
	m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Heirloom::Renderer::EndScene() { }

void Heirloom::Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,
                                const glm::mat4& transform)
{
	shader->Bind();
	std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection",
	                                                                   m_SceneData->ViewProjectionMatrix);
	std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
