#include "Heirloom.h"


#include "Heirloom/Application.h"
#include "Heirloom/Events/KeyEvent.h"
#include "Heirloom/Renderer/OrthographicCamera.h"


#include "imgui/imgui.h"

class ExampleLayer final : public Heirloom::Layer
{
public:
	ExampleLayer() : Layer("Example")
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

		// TODO: This is all temporary code, this needs to be moved to VertexArray
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
	
	void OnUpdate() override
	{		
		Heirloom::Renderer::Submit(m_BlueShader, m_SquareVA);
		Heirloom::Renderer::Submit(m_Shader, m_VertexArray);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Heirloom::Event& event) override
	{
		// HL_TRACE("{0}", event.ToString());

		// if (event.GetEventType() == Heirloom::EventType::KeyPressed)
		// {
		// 	Heirloom::KeyPressedEvent& e = static_cast<Heirloom::KeyPressedEvent&>(event);
		// 	HL_TRACE("{0}", static_cast<char>(e.GetKeyCode()));
		// }

		if (event.GetEventType() == Heirloom::EventType::KeyPressed)
		{
			Heirloom::KeyPressedEvent& e = static_cast<Heirloom::KeyPressedEvent&>(event);
			
			glm::vec3 cameraPosition = Heirloom::Application::Get().GetCamera()->GetPosition();
			float cameraRotation = Heirloom::Application::Get().GetCamera()->GetRotation();

			if (e.GetKeyCode() == HL_KEY_W)
			{
				cameraPosition.y += 0.25;
			}
			else if (e.GetKeyCode() == HL_KEY_S)
			{
				cameraPosition.y -= 0.25;
			}
			else if (e.GetKeyCode() == HL_KEY_D)
			{
				cameraPosition.x += 0.25;
			}
			else if (e.GetKeyCode() == HL_KEY_A)
			{
				cameraPosition.x -= 0.25;
			}
			else if (e.GetKeyCode() == HL_KEY_Q)
			{
				cameraRotation -= 45.0f;
			}
			else if (e.GetKeyCode() == HL_KEY_E)
			{
				cameraRotation += 45.0f;
			}

			Heirloom::Application::Get().GetCamera()->SetPosition(cameraPosition);
			Heirloom::Application::Get().GetCamera()->SetRotation(cameraRotation);
		}
	}

private:
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
