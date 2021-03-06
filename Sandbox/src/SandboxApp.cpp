// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#include "Heirloom.h"
#include "Sandbox2D.h"

// ReSharper disable once CppUnusedIncludeDirective
#include "Heirloom/Core/EntryPoint.h"

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer final : public Heirloom::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f, true) { }

	void OnAttach() override
	{
		#pragma region Initializing vertex arrays
		// Vertex Array
		m_VertexArray = Heirloom::VertexArray::Create();

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

		m_SquareVA = Heirloom::VertexArray::Create();

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

		const Heirloom::Ref<Heirloom::Shader> textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_FlatColorShader                                   = m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");

		m_Texture2D   = Heirloom::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Heirloom::Texture2D::Create("assets/textures/Logo.png");

		std::dynamic_pointer_cast<Heirloom::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Heirloom::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
		#pragma endregion
	}

	void OnDetach() override { }

	void OnUpdate(const Heirloom::Timestep ts) override
	{
		m_CameraController.Update(ts);

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

private:
	Heirloom::OrthographicCameraController m_CameraController;

	Heirloom::ShaderLibrary m_ShaderLibrary;
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
		// PushLayer(new ExampleLayer);
		PushLayer(new Sandbox2D);
		HL_INFO("Initialized Sandbox application");
	}

	~Sandbox() { }
};

Heirloom::Application* Heirloom::CreateApplication()
{
	return new Sandbox();
}
