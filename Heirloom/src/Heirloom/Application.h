#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"


#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"
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
		OrthographicCamera* GetCamera() const { return m_Camera; }
	private:
		// Private application methods
		bool OnWindowClose(WindowCloseEvent e);

		// Application variables
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		OrthographicCamera* m_Camera;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_SquareVA;
	};

	/**
	 * \brief Needs to be defined in the client application
	 * \return The application that needs to be executed
	 */
	Application* CreateApplication();
}
