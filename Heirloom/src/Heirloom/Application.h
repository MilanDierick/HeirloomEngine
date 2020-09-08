#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Heirloom
{
	class HL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run() const;

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent e);
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
