#include "Heirloom.h"
#include "Heirloom/Application.h"
#include "Heirloom/Events/KeyEvent.h"
#include "Heirloom/Renderer/OrthographicCamera.h"
#include "imgui/imgui.h"

class ExampleLayer final : public Heirloom::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		#pragma region Initializing vertex arrays
		// Vertex Array
		m_VertexArray.reset(Heirloom::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};

		std::shared_ptr<Heirloom::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Heirloom::VertexBuffer::Create(vertices, sizeof vertices));

		const Heirloom::BufferLayout layout = {
			{Heirloom::ShaderDataType::Float3, "a_Position"},
			{Heirloom::ShaderDataType::Float4, "a_Color"},
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = {0, 1, 2};
		std::shared_ptr<Heirloom::IndexBuffer> indexBuffer;
		indexBuffer.reset(Heirloom::IndexBuffer::Create(indices, sizeof indices / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Heirloom::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};

		std::shared_ptr<Heirloom::VertexBuffer> squareVB;
		squareVB.reset(Heirloom::VertexBuffer::Create(squareVertices, sizeof squareVertices));
		squareVB->SetLayout({
			                    {Heirloom::ShaderDataType::Float3, "a_Position"}
		                    });
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
		std::shared_ptr<Heirloom::IndexBuffer> squareIB;
		squareIB.reset(Heirloom::IndexBuffer::Create(squareIndices, sizeof squareIndices / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		const std::string vertexSource =
			R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
		
			out vec3 v_Position;
			out vec4 v_Color;
		
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Heirloom::Shader(vertexSource, fragmentSource));

		const std::string blueShaderVertexSource =
			R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
		
			out vec3 v_Position;
		
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		const std::string blueFragmentShaderSource =
			R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Heirloom::Shader(blueShaderVertexSource, blueFragmentShaderSource));
		#pragma endregion
	}

	void OnAttach() override { }
	void OnDetach() override { }
	
	void OnUpdate(const Heirloom::Timestep ts) override
	{
		HL_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());		
		
		if (Heirloom::Input::IsKeyPressed(HL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		
		else if (Heirloom::Input::IsKeyPressed(HL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		if (Heirloom::Input::IsKeyPressed(HL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		
		else if (Heirloom::Input::IsKeyPressed(HL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Heirloom::Input::IsKeyPressed(HL_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
			
		else if (Heirloom::Input::IsKeyPressed(HL_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		
		Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Heirloom::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		
		Heirloom::Renderer::BeginScene(m_Camera);
		
		Heirloom::Renderer::Submit(m_BlueShader, m_SquareVA);
		Heirloom::Renderer::Submit(m_Shader, m_VertexArray);

		Heirloom::Renderer::EndScene();
	}

	void OnImGuiRender() override { }
	void OnEvent(Heirloom::Event& event) override { }

private:
	Heirloom::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 50.0f;
	
	std::shared_ptr<Heirloom::Shader> m_Shader;
	std::shared_ptr<Heirloom::Shader> m_BlueShader;
	std::shared_ptr<Heirloom::VertexArray> m_VertexArray;
	std::shared_ptr<Heirloom::VertexArray> m_SquareVA;
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
