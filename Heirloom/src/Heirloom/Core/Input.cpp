#include "hlpch.h"
#include "Input.h"

namespace Heirloom
{
	Event<KeyPressedEventArgs> Input::KeyPressedEvent                   = Event<KeyPressedEventArgs>();
	Event<KeyReleasedEventArgs> Input::KeyReleasedEvent                 = Event<KeyReleasedEventArgs>();
	Event<KeyTypedEventArgs> Input::KeyTypedEvent                       = Event<KeyTypedEventArgs>();
	Event<MouseButtonPressedEventArgs> Input::MouseButtonPressedEvent   = Event<MouseButtonPressedEventArgs>();
	Event<MouseButtonReleasedEventArgs> Input::MouseButtonReleasedEvent = Event<MouseButtonReleasedEventArgs>();
	Event<MouseMovedEventArgs> Input::MouseMovedEvent                   = Event<MouseMovedEventArgs>();
	Event<MouseScrolledEventArgs> Input::MouseScrolledEvent             = Event<MouseScrolledEventArgs>();

	bool Input::IsKeyPressed(const int keycode)
	{
		return s_Instance->IsKeyPressedImpl(keycode);
	}

	bool Input::IsMouseButtonPressed(const int button)
	{
		return s_Instance->IsMouseButtonPressedImpl(button);
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		return s_Instance->GetMousePositionImpl();
	}

	float Input::GetMouseX()
	{
		return s_Instance->GetMouseXImpl();
	}

	float Input::GetMouseY()
	{
		return s_Instance->GetMouseYImpl();
	}
}
