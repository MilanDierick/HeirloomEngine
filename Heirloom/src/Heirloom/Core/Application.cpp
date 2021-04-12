﻿#include "hlpch.h"
#include "Application.h"
#include "GLFW/glfw3.h"

#include "Heirloom/Audio/SoundService.h"
#include "Heirloom/Renderer/Renderer.h"
#include "Heirloom/Scenes/SceneManager.h"

#define MS_PER_TICK 1000 / 144

namespace Heirloom
{
	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HL_PROFILE_FUNCTION()

		HL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->WindowResizedEvent += HL_BIND_EVENT_FN(Application::OnWindowResizedEvent);
		m_Window->WindowClosedEvent += HL_BIND_EVENT_FN(Application::OnWindowClosedEvent);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		m_ImGuiLayer->OnAttach();
	}

	Application::~Application()
	{
		SceneManager::RemoveAllScenes();
		m_ImGuiLayer->OnDetach();
	}

	// TODO: A cheap solution is to walk the list backwards when you update. That way removing an object only shifts items that were already updated.
	// ReSharper disable once CppMemberFunctionMayBeConst
	void Application::Run()
	{
		HL_PROFILE_FUNCTION()

		std::chrono::steady_clock::time_point previousTimePoint = std::chrono::steady_clock::now();
		double lag                                              = 0.0;

		while (m_IsRunning)
		{
			HL_PROFILE_SCOPE("Frame")

			const std::chrono::time_point<std::chrono::steady_clock> currentTimePoint =
				std::chrono::steady_clock::now();

			const auto elapsedTime = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTimePoint).
				time_since_epoch() - std::chrono::time_point_cast<std::chrono::milliseconds>(previousTimePoint).
				time_since_epoch();

			previousTimePoint = currentTimePoint;

			lag += elapsedTime.count();

			m_Window->OnUpdate();

			if (m_Minimized) continue;

			while (lag >= MS_PER_TICK)
			{
				{
					HL_PROFILE_SCOPE("LayerStack OnUpdate")

					SceneManager::Update();
				}

				lag -= MS_PER_TICK;
			}

			SoundService::GetSoundEngine()->Update();

			{
				HL_PROFILE_SCOPE("LayerStack OnRender")

				SceneManager::Render();
			}

			m_ImGuiLayer->Begin();

			{
				HL_PROFILE_SCOPE("LayerStack OnImGuiRender")

				SceneManager::ImGuiRender();
			}

			m_ImGuiLayer->End();
		}
	}

	bool Application::OnWindowClosedEvent(const WindowClosedEventArgs)
	{
		HL_PROFILE_FUNCTION()

		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEventArgs eventArgs)
	{
		HL_PROFILE_FUNCTION()

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
