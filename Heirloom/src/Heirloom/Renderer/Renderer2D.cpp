#include "hlpch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

void Heirloom::Renderer2D::Init()
{
	HL_PROFILE_FUNCTION();

	s_Data.QuadVertexArray = VertexArray::Create();

	s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
	s_Data.QuadVertexBuffer->SetLayout({
		{ShaderDataType::Float3, "a_Position"},
		{ShaderDataType::Float4, "a_Color"},
		{ShaderDataType::Float2, "a_TexCoord"}
	});
	s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

	s_Data.pQuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

	uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

	uint32_t offset = 0;
	for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
	{
		quadIndices[i + 0] = offset + 0;
		quadIndices[i + 1] = offset + 1;
		quadIndices[i + 2] = offset + 2;

		quadIndices[i + 3] = offset + 2;
		quadIndices[i + 4] = offset + 3;
		quadIndices[i + 5] = offset + 0;

		offset += 4;
	}

	const Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
	s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
	delete[] quadIndices;

	s_Data.WhiteTexture       = Texture2D::Create(1, 1);
	uint32_t whiteTextureData = 0xffffffff;
	s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

	s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
	s_Data.TextureShader->Bind();
	s_Data.TextureShader->SetInt("u_Texture", 0);
}

void Heirloom::Renderer2D::Shutdown()
{
	HL_PROFILE_FUNCTION()
}

void Heirloom::Renderer2D::BeginScene(OrthographicCamera& camera)
{
	HL_PROFILE_FUNCTION()
	
	s_Data.TextureShader->Bind();
	s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

	s_Data.QuadIndexCount    = 0;
	s_Data.pQuadVertexBuffer = s_Data.pQuadVertexBufferBase;
}

void Heirloom::Renderer2D::EndScene()
{
	HL_PROFILE_FUNCTION()
	
	const uint32_t dataSize = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(s_Data.pQuadVertexBuffer) - reinterpret_cast<uint8_t*>(s_Data.
		pQuadVertexBufferBase));
	s_Data.QuadVertexBuffer->SetData(s_Data.pQuadVertexBufferBase, dataSize);

	Flush();
}

void Heirloom::Renderer2D::Flush() { RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount); }

void Heirloom::Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Heirloom::Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	HL_PROFILE_FUNCTION()
	
	s_Data.pQuadVertexBuffer->Position = position;
	s_Data.pQuadVertexBuffer->Color    = color;
	s_Data.pQuadVertexBuffer->TexCoord = {0.0f, 0.0f};
	s_Data.pQuadVertexBuffer++;

	s_Data.pQuadVertexBuffer->Position = {position.x + size.x, position.y, 0.0f};
	s_Data.pQuadVertexBuffer->Color    = color;
	s_Data.pQuadVertexBuffer->TexCoord = {1.0f, 0.0f};
	s_Data.pQuadVertexBuffer++;

	s_Data.pQuadVertexBuffer->Position = {position.x + size.x, position.y + size.y, 0.0f};
	s_Data.pQuadVertexBuffer->Color    = color;
	s_Data.pQuadVertexBuffer->TexCoord = {1.0f, 1.0f};
	s_Data.pQuadVertexBuffer++;

	s_Data.pQuadVertexBuffer->Position = {position.x, position.y + size.y, 0.0f};
	s_Data.pQuadVertexBuffer->Color    = color;
	s_Data.pQuadVertexBuffer->TexCoord = {0.0f, 1.0f};
	s_Data.pQuadVertexBuffer++;

	s_Data.QuadIndexCount += 6;

	s_Data.TextureShader->SetFloat4("u_Color", color);
	s_Data.TextureShader->SetFloat("u_TexTilingFactor", 1.0f);

	s_Data.WhiteTexture->Bind();
}

void Heirloom::Renderer2D::DrawQuad(const glm::vec2& position,
									const glm::vec2& size,
									const Ref<Texture2D>& texture,
									const float tilingFactor,
									const glm::vec4& tintColor)
{
	DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
}

void Heirloom::Renderer2D::DrawQuad(const glm::vec3& position,
									const glm::vec2& size,
									const Ref<Texture2D>& texture,
									const float tilingFactor,
									const glm::vec4& tintColor)
{
	HL_PROFILE_FUNCTION()
	
	s_Data.TextureShader->SetFloat4("u_Color", tintColor);
	s_Data.TextureShader->SetFloat("u_TexTilingFactor", tilingFactor);

	texture->Bind();

	const float aspectRatio = static_cast<float>(texture->GetWidth()) / static_cast<float>(texture->GetHeight());

	const glm::mat4 transform = translate(glm::mat4(1.0f), position) * scale(
		glm::mat4(1.0f),
		{size.x, size.y / aspectRatio, 1.0f});

	s_Data.TextureShader->SetMat4("u_Transform", transform);

	s_Data.QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
}

void Heirloom::Renderer2D::DrawQuad(Sprite& sprite)
{
	DrawQuad(sprite.Position, sprite.Size, sprite.Texture, sprite.TilingFactor, sprite.TintColor);
}

void Heirloom::Renderer2D::DrawRotatedQuad(const glm::vec2& position,
										   const glm::vec2& size,
										   const float rotation,
										   const glm::vec4& color)
{
	DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
}

void Heirloom::Renderer2D::DrawRotatedQuad(const glm::vec3& position,
										   const glm::vec2& size,
										   const float rotation,
										   const glm::vec4& color)
{
	HL_PROFILE_FUNCTION()
	
	s_Data.TextureShader->SetFloat4("u_Color", color);
	s_Data.TextureShader->SetFloat("u_TexTilingFactor", 1.0f);

	s_Data.WhiteTexture->Bind();

	const glm::mat4 transform = translate(glm::mat4(1.0f), position) * rotate(
		glm::mat4(1.0f),
		rotation,
		{0.0f, 0.0f, 1.0f}) * scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

	s_Data.TextureShader->SetMat4("u_Transform", transform);

	s_Data.QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
}

void Heirloom::Renderer2D::DrawRotatedQuad(const glm::vec2& position,
										   const glm::vec2& size,
										   const float rotation,
										   const Ref<Texture2D>& texture,
										   const float tilingFactor,
										   const glm::vec4& tintColor)
{
	DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
}

void Heirloom::Renderer2D::DrawRotatedQuad(const glm::vec3& position,
										   const glm::vec2& size,
										   const float rotation,
										   const Ref<Texture2D>& texture,
										   const float tilingFactor,
										   const glm::vec4& tintColor)
{
	HL_PROFILE_FUNCTION()
	
	s_Data.TextureShader->SetFloat4("u_Color", tintColor);
	s_Data.TextureShader->SetFloat("u_TexTilingFactor", tilingFactor);

	texture->Bind();

	const float aspectRatio = static_cast<float>(texture->GetWidth()) / static_cast<float>(texture->GetHeight());

	const glm::mat4 transform = translate(glm::mat4(1.0f), position) *
		rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * scale(glm::mat4(1.0f),
																	  {size.x, size.y / aspectRatio, 1.0f});

	s_Data.TextureShader->SetMat4("u_Transform", transform);

	s_Data.QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
}

void Heirloom::Renderer2D::DrawRotatedQuad(Sprite& sprite)
{
	DrawRotatedQuad(sprite.Position,
					sprite.Size,
					sprite.Rotation,
					sprite.Texture,
					sprite.TilingFactor,
					sprite.TintColor);
}
