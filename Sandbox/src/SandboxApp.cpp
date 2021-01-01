#include "Heirloom.h"
#include "imgui/imgui.h"

class ExampleLayer final : public Heirloom::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		// HL_INFO("ExampleLayer::Update");
		
		if (Heirloom::Input::IsKeyPressed(HL_KEY_TAB))
		{
			HL_INFO("Tab key is pressed!");
		}
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
	}
};

class Sandbox final : public Heirloom::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
		HL_INFO("Initialized Sandbox application");
	}

	~Sandbox()
	{
		
	}
};

Heirloom::Application* Heirloom::CreateApplication()
{
	return new Sandbox();
}