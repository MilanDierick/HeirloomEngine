#pragma once
#include "Heirloom/Window.h"
#include "GLFW/glfw3.h"
#include "Heirloom/Renderer/GraphicsContext.h"

namespace Heirloom
{
	class WindowsWindow final : public Window
	{
	public:
		explicit WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

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
		GraphicsContext *m_Context;

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
