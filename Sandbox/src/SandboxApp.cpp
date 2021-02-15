#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include "Heirloom.h"
#include "Heirloom/Application.h"
#include "Heirloom/Events/KeyEvent.h"
#include "Heirloom/Renderer/OrthographicCamera.h"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer final : public Heirloom::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) { }

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

		Heirloom::Ref<Heirloom::VertexBuffer> vertexBuffer;
		vertexBuffer = Heirloom::VertexBuffer::Create(vertices, sizeof vertices);

		const Heirloom::BufferLayout layout = {
			{Heirloom::ShaderDataType::Float3, "a_Position"},
			{Heirloom::ShaderDataType::Float4, "a_Color"},
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = {0, 1, 2};
		Heirloom::Ref<Heirloom::IndexBuffer> indexBuffer;
		indexBuffer = Heirloom::IndexBuffer::Create(indices, sizeof indices / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Heirloom::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		Heirloom::Ref<Heirloom::VertexBuffer> squareVB;
		squareVB = Heirloom::VertexBuffer::Create(squareVertices, sizeof squareVertices);
		squareVB->SetLayout({
			                    {Heirloom::ShaderDataType::Float3, "a_Position"},
			                    {Heirloom::ShaderDataType::Float2, "a_TexCoord"}
		                    });
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
		Heirloom::Ref<Heirloom::IndexBuffer> squareIB;
		squareIB = Heirloom::IndexBuffer::Create(squareIndices, sizeof squareIndices / sizeof(uint32_t));
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

		m_Shader = Heirloom::Shader::Create(vertexSource, fragmentSource);

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

		m_FlatColorShader = Heirloom::Shader::Create(flatColorShaderVertexSource, flatColorFragmentShaderSource);

		const std::string textureShaderVertexSource =
			R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
		
			out vec2 v_TexCoord;
		
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		const std::string textureFragmentShaderSource =
			R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;
		
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader = Heirloom::Shader::Create(textureShaderVertexSource, textureFragmentShaderSource);

		m_Texture2D = Heirloom::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Heirloom::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Heirloom::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
		#pragma endregion
	}

	void OnDetach() override { }

	void OnUpdate(const Heirloom::Timestep ts) override
	{
		// Viewport movement
		if (Heirloom::Input::IsKeyPressed(HL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		else if (Heirloom::Input::IsKeyPressed(HL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		if (Heirloom::Input::IsKeyPressed(HL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Heirloom::Input::IsKeyPressed(HL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		// Viewport rotation
		if (Heirloom::Input::IsKeyPressed(HL_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Heirloom::Input::IsKeyPressed(HL_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Heirloom::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Heirloom::Renderer::BeginScene(m_Camera);

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

		m_Texture2D->Bind();
		Heirloom::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		// Triangle
		// Heirloom::Renderer::Submit(m_Shader, m_VertexArray);

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

	void OnEvent(Heirloom::Event&) override { }

private:
	Heirloom::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed     = 2.5f;
	float m_CameraRotation      = 0.0f;
	float m_CameraRotationSpeed = 50.0f;

	Heirloom::Ref<Heirloom::Shader> m_Shader;
	Heirloom::Ref<Heirloom::Shader> m_FlatColorShader, m_TextureShader;
	Heirloom::Ref<Heirloom::VertexArray> m_VertexArray;
	Heirloom::Ref<Heirloom::VertexArray> m_SquareVA;

	Heirloom::Ref<Heirloom::Texture2D> m_Texture2D;

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
