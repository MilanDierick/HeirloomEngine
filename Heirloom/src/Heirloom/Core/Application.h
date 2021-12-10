// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_APPLICATION_H
#define HEIRLOOM_APPLICATION_H

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Heirloom/ImGui/ImGuiLayer.h"

namespace Heirloom
{
	/**
	 * \brief Contains application-specific code to properly start and manage the core game loop\n
	 * The client application should derive from this
	 */
	class Application
	{
	public:
		Application();
		virtual ~Application();

		/**
		 * \brief Starts the core game loop
		 */
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();

		ImGuiLayer* GetImGuiLayer() const;
		static Application& Get();

		Window& GetWindow() const;

	private:
		// Private application methods
		bool OnWindowClosedEvent(WindowClosedEventArgs eventArgs);
		bool OnWindowResizedEvent(WindowResizedEventArgs eventArgs);

		// Application variables
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_IsRunning = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	/**
	 * \brief Needs to be defined in the client application
	 * \return The application that needs to be executed
	 */
	Application* CreateApplication();
}

#endif //HEIRLOOM_APPLICATION_H
