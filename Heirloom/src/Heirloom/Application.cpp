#include "hlpch.h"
#include "Application.h"
#include "GLFW/glfw3.h"
#include "Renderer/Renderer.h"

namespace Heirloom
{
	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->WindowResizedEvent += HL_BIND_EVENT_FN(Application::OnWindowResizedEvent);
		m_Window->WindowClosedEvent += HL_BIND_EVENT_FN(Application::OnWindowClosedEvent);
		
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() { }

	void Application::Run()
	{
		while (m_IsRunning)
		{
			// TODO: Move this to a platform-dependant file
			const float time = static_cast<float>(glfwGetTime());
			const Timestep timestep(time - m_LastFrameTime);
			m_LastFrameTime = time;
		
			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}
		
			m_ImGuiLayer->Begin();
		
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
		
			m_ImGuiLayer->End();
		
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClosedEvent(const WindowClosedEventArgs)
	{
		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEventArgs eventArgs)
	{
		if (eventArgs.Width == 0 || eventArgs.Height == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(eventArgs.Width, eventArgs.Height);

		return false;
	}
}
