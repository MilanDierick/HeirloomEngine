#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent e);
		
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
