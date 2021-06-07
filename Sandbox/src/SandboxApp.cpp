// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#include "Heirloom.h"
#include "Sandbox2D.h"

// ReSharper disable once CppUnusedIncludeDirective
#include "Heirloom/Core/EntryPoint.h"

class Sandbox final : public Heirloom::Application
{
public:
	Sandbox()
	{
		HL_PROFILE_FUNCTION()

		PushLayer(new Sandbox2D);
		HL_INFO("Initialized Sandbox application");
	}

	~Sandbox() override
	{
	}
};

Heirloom::Application* Heirloom::CreateApplication()
{
	HL_PROFILE_FUNCTION()

	return new Sandbox();
}
