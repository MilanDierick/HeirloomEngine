#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/VertexArray.h"

namespace Heirloom
{
	/**
	 * \brief Contains application-specific code to properly start and manage the core game loop\n
	 * The client application should derive from this
	 */
	class HL_API Application
	{
	public:
		Application();
		virtual ~Application();

		/**
		 * \brief Starts the core game loop
		 */
		void Run();

		/**
		* \brief Is executed whenever an event is fired by the window management library or the application itself
		* \param e The event that has been fired
		*/
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }
		
	private:
		// Private application methods
		bool OnWindowClose(WindowCloseEvent e);

		// Application variables
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		float m_LastFrameTime = 0.0f;
	};

	/**
	 * \brief Needs to be defined in the client application
	 * \return The application that needs to be executed
	 */
	Application* CreateApplication();
}
