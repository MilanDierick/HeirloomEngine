﻿// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "GLFW/glfw3.h"

#include "Heirloom/Window.h"
#include "Heirloom/Renderer/GraphicsContext.h"

namespace Heirloom
{
	class WindowsWindow final : public Window
	{
	public:
		explicit WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		WindowsWindow(const WindowsWindow& other)                = delete;
		WindowsWindow(WindowsWindow&& other) noexcept            = delete;
		WindowsWindow& operator=(const WindowsWindow& other)     = delete;
		WindowsWindow& operator=(WindowsWindow&& other) noexcept = delete;

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override { return m_Window; }

	private:
		void Init(const WindowProps& props);
		void Shutdown() const;

		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
