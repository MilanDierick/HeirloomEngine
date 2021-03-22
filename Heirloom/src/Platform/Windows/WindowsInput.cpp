#include "hlpch.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "Heirloom/Core/Application.h"

namespace Heirloom
{
	Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(const int keycode)
	{
		HL_PROFILE_FUNCTION()
    	
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const int state    = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(const int button)
	{
		HL_PROFILE_FUNCTION()
    	
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const int state    = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		HL_PROFILE_FUNCTION()
    	
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return {static_cast<float>(xPos), static_cast<float>(yPos)};
	}

	bool WindowsInput::GetMouseXImpl()
	{
		HL_PROFILE_FUNCTION()
    	
		auto [x, y] = GetMousePositionImpl();

		return x;
	}

	bool WindowsInput::GetMouseYImpl()
	{
		HL_PROFILE_FUNCTION()
	
		auto [x, y] = GetMousePositionImpl();

		return y;
	}
}
