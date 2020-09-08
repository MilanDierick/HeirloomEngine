#include "Heirloom.h"

class ExampleLayer : public Heirloom::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		HL_INFO("ExampleLayer::Update");
	}

	void OnEvent(Heirloom::Event& event) override
	{
		HL_TRACE("{0}", event.ToString());
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