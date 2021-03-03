// Author: Milan Dierick
// Created: 03/03/2021 2:47 AM
// Solution: HeirloomEngine

#pragma once
#include "EventNew.h"

namespace Heirloom
{
	struct HL_API WindowResizedEventArgs : EventArgs
	{
		[[nodiscard]] WindowResizedEventArgs(const unsigned width, const unsigned height)
			: Width(width),
			  Height(height) {}

		unsigned int Width, Height;
	};

	struct HL_API WindowClosedEventArgs : EventArgs
	{
	
	};

	struct HL_API AppTickEventArgs : EventArgs
	{
	
	};

	struct HL_API AppUpdatedEventArgs : EventArgs
	{
	
	};

	struct HL_API AppRenderEventArgs : EventArgs
	{
	
	};
}
