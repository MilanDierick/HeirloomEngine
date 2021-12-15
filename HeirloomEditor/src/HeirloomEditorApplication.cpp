// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#include "Heirloom.h"
#include "EditorLayer.h"

// ReSharper disable once CppUnusedIncludeDirective
#include "Heirloom/Core/EntryPoint.h"

namespace Heirloom
{
	class EditorApplication final : public Application
	{
	public:
		EditorApplication()
		{
			HL_PROFILE_FUNCTION()

			PushLayer(new EditorLayer());
			HL_INFO("Initialized Sandbox application");
		}
	};

	Application* CreateApplication()
	{
		HL_PROFILE_FUNCTION()

		return new EditorApplication();
	}
}
