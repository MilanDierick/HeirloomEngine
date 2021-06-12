// Author: Milan Dierick
// Created: 03/03/2021 2:37 AM
// Solution: HeirloomEngine

#pragma once
#include "Event.h"

namespace Heirloom
{
	struct MouseMovedEventArgs : EventArgs
	{
		[[nodiscard]] MouseMovedEventArgs(const float mouseX, const float mouseY)
			: MouseX(mouseX),
			  MouseY(mouseY)
		{
		}

		float MouseX, MouseY;
	};

	struct MouseScrolledEventArgs : EventArgs
	{
		[[nodiscard]] MouseScrolledEventArgs(const float xOffset, const float yOffset)
			: XOffset(xOffset),
			  YOffset(yOffset)
		{
		}

		float XOffset, YOffset;
	};

	struct MouseButtonPressedEventArgs : EventArgs
	{
		[[nodiscard]] explicit MouseButtonPressedEventArgs(const int button)
			: Button(button)
		{
		}

		int Button;
	};

	struct MouseButtonReleasedEventArgs : EventArgs
	{
		[[nodiscard]] explicit MouseButtonReleasedEventArgs(const int button)
			: Button(button)
		{
		}

		int Button;
	};
}
