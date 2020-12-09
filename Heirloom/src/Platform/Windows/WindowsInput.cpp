#include "hlpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Heirloom/Application.h"

namespace Heirloom
{
	Input* Input::s_Instance = new WindowsInput();
	
	bool WindowsInput::IsKeyPressedImpl(const int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const int state    = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(const int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const int state    = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return {static_cast<float>(xPos), static_cast<float>(yPos)};
	}

	bool WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePositionImpl();

		return static_cast<float>(x);
	}

	bool WindowsInput::GetMouseYImpl()
	{
		auto[x, y] = GetMousePositionImpl();

		return static_cast<float>(y);
	}
}
