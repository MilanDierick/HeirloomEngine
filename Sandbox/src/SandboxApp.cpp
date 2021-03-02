// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include "Heirloom.h"
#include "Heirloom/Application.h"
#include "Heirloom/OrthographicCameraController.h"
#include "Heirloom/Renderer/OrthographicCamera.h"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer final : public Heirloom::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f) { }

	void OnAttach() override
	{
		#pragma region Initializing vertex arrays
		// Vertex Array
		m_VertexArray.reset(Heirloom::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};

		Heirloom::Ref<Heirloom::VertexBuffer> vertexBuffer = Heirloom::VertexBuffer::Create(vertices, sizeof vertices);

		const Heirloom::BufferLayout layout = {
			{Heirloom::ShaderDataType::Float3, "a_Position"},
			{Heirloom::ShaderDataType::Float4, "a_Color"},
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3]                                    = {0, 1, 2};
		const Heirloom::Ref<Heirloom::IndexBuffer> indexBuffer =
			Heirloom::IndexBuffer::Create(indices, sizeof indices / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Heirloom::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		Heirloom::Ref<Heirloom::VertexBuffer> squareVB = Heirloom::VertexBuffer::Create(squareVertices,
			sizeof squareVertices);
		squareVB->SetLayout({
			                    {Heirloom::ShaderDataType::Float3, "a_Position"},
			                    {Heirloom::ShaderDataType::Float2, "a_TexCoord"}
		                    });
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6]                           = {0, 1, 2, 2, 3, 0};
		const Heirloom::Ref<Heirloom::IndexBuffer> squareIB = Heirloom::IndexBuffer::Create(squareIndices,
			sizeof squareIndices / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		const std::string vertexSource =
			R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
		
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		const std::string fragmentSource =
			R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}

		)";

		m_Shader = Heirloom::Shader::Create("VertexPosColor", vertexSource, fragmentSource);

		const std::string flatColorShaderVertexSource =
			R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
		
			out vec3 v_Position;
		
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		const std::string flatColorFragmentShaderSource =
			R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;
		
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Heirloom::Shader::Create("FlatColor", flatColorShaderVertexSource,
		                                             flatColorFragmentShaderSource);

		const Heirloom::Ref<Heirloom::Shader> textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture2D   = Heirloom::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Heirloom::Texture2D::Create("assets/textures/Logo.png");

		std::dynamic_pointer_cast<Heirloom::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Heirloom::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
		#pragma endregion
	}

	void OnDetach() override { }

	void OnUpdate(const Heirloom::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		// Render
		Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Heirloom::RenderCommand::Clear();

		for (std::vector<Heirloom::GameObject>::value_type gameObject : m_GameObjects)
		{
			gameObject.Update(ts);
		}

		Heirloom::Renderer::BeginScene(m_CameraController.GetCamera());

		const glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Heirloom::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Heirloom::OpenGLShader>(m_FlatColorShader)->
			UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				const glm::mat4 transform = translate(glm::mat4(1.0f), pos) * scale;
				Heirloom::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		const Heirloom::Ref<Heirloom::Shader> textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture2D->Bind();
		Heirloom::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		m_LogoTexture->Bind();
		Heirloom::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		// Triangle
		// Heirloom::Renderer::Submit(m_Shader, m_VertexArray);

		for (std::vector<Heirloom::GameObject>::value_type gameObject : m_GameObjects)
		{
			gameObject.Render();
		}

		Heirloom::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", value_ptr(m_SquareColor));
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(10, 10));
		ImGui::Begin("main", nullptr,
		             ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::SetWindowFontScale(2.0);
		ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void OnEvent(Heirloom::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

private:
	Heirloom::OrthographicCameraController m_CameraController;

	Heirloom::ShaderLibrary m_ShaderLibrary;
	Heirloom::Ref<Heirloom::Shader> m_Shader;
	Heirloom::Ref<Heirloom::Shader> m_FlatColorShader;
	Heirloom::Ref<Heirloom::VertexArray> m_VertexArray;
	Heirloom::Ref<Heirloom::VertexArray> m_SquareVA;

	Heirloom::Ref<Heirloom::Texture2D> m_Texture2D, m_LogoTexture;

	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox final : public Heirloom::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
		HL_INFO("Initialized Sandbox application");
	}

	~Sandbox() { }
};

Heirloom::Application* Heirloom::CreateApplication()
{
	return new Sandbox();
}
