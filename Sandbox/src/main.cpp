#include "Heirloom.h"

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
	}

	~Sandbox()
	{
		
	}
};

Heirloom::Application* Heirloom::CreateApplication()
{
	return new Sandbox();
}