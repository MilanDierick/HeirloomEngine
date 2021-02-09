#include "hlpch.h"
#include "Renderer.h"

void Heirloom::Renderer::BeginScene()
{
	
}

void Heirloom::Renderer::EndScene()
{
	
}

void Heirloom::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
{
	// vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
