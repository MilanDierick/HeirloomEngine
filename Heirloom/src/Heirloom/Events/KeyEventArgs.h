// Author: Milan Dierick
// Created: 03/03/2021 2:41 AM
// Solution: HeirloomEngine

#pragma once
#include "Event.h"

namespace Heirloom
{
	struct KeyEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyEventArgs(const KeyCode keyCode)
			: KeyCode(keyCode)
		{
		}

		KeyCode KeyCode;
	};

	struct KeyPressedEventArgs : EventArgs
	{
		[[nodiscard]] KeyPressedEventArgs(const KeyCode keyCode, const int repeatCount)
			: KeyCode(keyCode),
			  RepeatCount(repeatCount)
		{
		}

		KeyCode KeyCode;
		int RepeatCount;
	};

	struct KeyReleasedEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyReleasedEventArgs(const KeyCode keyCode)
			: KeyCode(keyCode)
		{
		}

		KeyCode KeyCode;
	};

	struct KeyTypedEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyTypedEventArgs(const KeyCode keyCode)
			: KeyCode(keyCode)
		{
		}

		KeyCode KeyCode;
	};
}
