#include "hlpch.h"
#include "Renderer.h"

#include "Shader.h"

Heirloom::Renderer::SceneData* Heirloom::Renderer::m_SceneData = new SceneData;

void Heirloom::Renderer::BeginScene(OrthographicCamera& camera)
{
	m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Heirloom::Renderer::EndScene()
{
	
}

void Heirloom::Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
{
	shader->Bind();
	shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
	
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
