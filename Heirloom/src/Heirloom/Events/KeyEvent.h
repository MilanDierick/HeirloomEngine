#pragma once

#include "Event.h"

namespace Heirloom
{
	class HL_API KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
	protected:
		~KeyEvent() = default;

		explicit KeyEvent(const int keycode)
			: m_KeyCode(keycode)
		{
		}

		int m_KeyCode;
	};

	class HL_API KeyPressedEvent final : public KeyEvent
	{
	public:
		KeyPressedEvent(const int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount)
		{
		}

		int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
		
	private:
		int m_RepeatCount;
	};

	class HL_API KeyReleasedEvent final : public KeyEvent
	{
	public:
		explicit KeyReleasedEvent(int keycode)
			: KeyEvent(keycode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
