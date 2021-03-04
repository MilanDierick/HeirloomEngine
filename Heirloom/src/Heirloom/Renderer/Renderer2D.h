// Author: Milan Dierick
// Created: 04/03/2021 10:58 PM
// Solution: HeirloomEngine

#pragma once
#include "OrthographicCamera.h"
#include "Shader.h"
#include "VertexArray.h"

namespace Heirloom
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data;

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
	
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};
}
