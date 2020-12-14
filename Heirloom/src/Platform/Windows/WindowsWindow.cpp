#include "hlpch.h"
#include "WindowsWindow.h"


#include "Heirloom/Events/ApplicationEvent.h"
#include "Heirloom/Events/KeyEvent.h"
#include "Heirloom/Events/MouseEvent.h"
#include "glad/glad.h"

namespace Heirloom
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(const int error, const char* description)
	{
		//HL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(const bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title  = props.Title;
		m_Data.Width  = props.Width;
		m_Data.Height = props.Height;

		HL_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			const int success = glfwInit();
			HL_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height),
		                            m_Data.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		HL_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, const int width, const int height)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->Width      = width;
			data->Height     = height;

			WindowResizeEvent event(width, height);
			data->EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			WindowCloseEvent event;
			data->EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, const int key, int scancode, const int action, int mods)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data->EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data->EventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data->EventCallback(event);
					break;
				}
			default:
				//HL_CORE_ERROR("Tried to process missing GLFW key action");
				break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			KeyTypedEvent event(keycode);

			data->EventCallback(event);
		});
		
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data->EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data->EventCallback(event);
					break;
				}
			default:
				//HL_CORE_ERROR("Tried to process missing GLFW key action");
				break;
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, const double xOffset, const double yOffset)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data->EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, const double xPos, const double yPos)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			data->EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown() const
	{
		glfwDestroyWindow(m_Window);
	}
}
