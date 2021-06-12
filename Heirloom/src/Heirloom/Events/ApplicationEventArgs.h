// Author: Milan Dierick
// Created: 03/03/2021 2:47 AM
// Solution: HeirloomEngine

#pragma once
#include "Event.h"

namespace Heirloom
{
	struct WindowResizedEventArgs : EventArgs
	{
		[[nodiscard]] WindowResizedEventArgs(const unsigned width, const unsigned height)
			: Width(width),
			  Height(height)
		{
		}

		unsigned int Width, Height;
	};

	struct WindowClosedEventArgs : EventArgs
	{
	};

	struct AppTickEventArgs : EventArgs
	{
	};

	struct AppUpdatedEventArgs : EventArgs
	{
	};

	struct AppRenderEventArgs : EventArgs
	{
	};
}
