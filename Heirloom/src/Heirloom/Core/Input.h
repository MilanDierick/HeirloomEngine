// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Events/EventNew.h"
#include "Heirloom/Events/KeyEventArgs.h"
#include "Heirloom/Events/MouseEventArgs.h"
#include "Heirloom/Core/Core.h"

namespace Heirloom
{
	class HL_API Input
	{
	public:
		inline static EventNew<KeyPressedEventArgs> KeyPressedEvent = EventNew<KeyPressedEventArgs>();
		inline static EventNew<KeyReleasedEventArgs> KeyReleasedEvent = EventNew<KeyReleasedEventArgs>();
		inline static EventNew<KeyTypedEventArgs> KeyTypedEvent = EventNew<KeyTypedEventArgs>();
		inline static EventNew<MouseButtonPressedEventArgs> MouseButtonPressedEvent = EventNew<MouseButtonPressedEventArgs>();
		inline static EventNew<MouseButtonReleasedEventArgs> MouseButtonReleasedEvent = EventNew<MouseButtonReleasedEventArgs>();
		inline static EventNew<MouseMovedEventArgs> MouseMovedEvent = EventNew<MouseMovedEventArgs>();
		inline static EventNew<MouseScrolledEventArgs> MouseScrolledEvent = EventNew<MouseScrolledEventArgs>();

		static bool IsKeyPressed(const int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(const int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		Input()  = default;
		~Input() = default;

		Input(const Input& other)     = default;
		Input(Input&& other) noexcept = default;

		Input& operator=(const Input& other)
		{
			if (this == &other)
				return *this;
			return *this;
		}

		Input& operator=(Input&& other) noexcept
		{
			if (this == &other)
				return *this;
			return *this;
		}

		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual bool GetMouseXImpl() = 0;
		virtual bool GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}
