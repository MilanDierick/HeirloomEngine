// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "KeyCodes.h"
#include "Heirloom/Events/Event.h"
#include "Heirloom/Events/KeyEventArgs.h"
#include "Heirloom/Events/MouseEventArgs.h"

namespace Heirloom
{
	class Input final
	{
	public:
		static Event<KeyPressedEventArgs> KeyPressedEvent;
		static Event<KeyReleasedEventArgs> KeyReleasedEvent;
		static Event<KeyTypedEventArgs> KeyTypedEvent;
		static Event<MouseButtonPressedEventArgs> MouseButtonPressedEvent;
		static Event<MouseButtonReleasedEventArgs> MouseButtonReleasedEvent;
		static Event<MouseMovedEventArgs> MouseMovedEvent;
		static Event<MouseScrolledEventArgs> MouseScrolledEvent;

		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
