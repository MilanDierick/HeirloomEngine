#include "hlpch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

void Heirloom::Renderer2D::Init()
{
	s_Data = new Renderer2DStorage();

	s_Data->QuadVertexArray = VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};

	Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices,
	                                                  sizeof squareVertices);
	squareVB->SetLayout({
		                    {ShaderDataType::Float3, "a_Position"}
	                    });
	s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6]       = {0, 1, 2, 2, 3, 0};
	const Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices,
	                                                      sizeof squareIndices / sizeof(uint32_t));
	s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

	s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
}

void Heirloom::Renderer2D::Shutdown()
{
	delete s_Data;
}

void Heirloom::Renderer2D::BeginScene(OrthographicCamera& camera)
{
	s_Data->FlatColorShader->Bind();
	s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Heirloom::Renderer2D::EndScene() { }

void Heirloom::Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Heirloom::Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	s_Data->FlatColorShader->Bind();
	s_Data->FlatColorShader->SetFloat4("u_Color", color);

	const glm::mat4 transform = translate(glm::mat4(1.0f), position) * /* rotation * */ scale(glm::mat4(1.0f),
		{size.x, size.y, 1.0f});

	s_Data->FlatColorShader->SetMat4("u_Transform", transform);

	s_Data->QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}
