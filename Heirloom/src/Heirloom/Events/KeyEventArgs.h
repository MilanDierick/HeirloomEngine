// Author: Milan Dierick
// Created: 03/03/2021 2:41 AM
// Solution: HeirloomEngine

#pragma once
#include "Event.h"

namespace Heirloom
{
	struct KeyEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyEventArgs(const int keyCode)
			: KeyCode(keyCode)
		{
		}

		int KeyCode;
	};

	struct KeyPressedEventArgs : EventArgs
	{
		[[nodiscard]] KeyPressedEventArgs(const int keyCode, const int repeatCount)
			: KeyCode(keyCode),
			  RepeatCount(repeatCount)
		{
		}

		int KeyCode;
		int RepeatCount;
	};

	struct KeyReleasedEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyReleasedEventArgs(const int keyCode)
			: KeyCode(keyCode)
		{
		}

		int KeyCode;
	};

	struct KeyTypedEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyTypedEventArgs(const int keyCode)
			: KeyCode(keyCode)
		{
		}

		int KeyCode;
	};
}
