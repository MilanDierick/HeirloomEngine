// Author: Milan Dierick
// Created: 28/03/2021 7:17 PM
// Solution: HeirloomEngine

#pragma once

namespace Heirloom
{
	struct Sound
	{
		std::string FileName;
		float Volume    = 1.0f;
		bool ShouldLoop = false;
	};
}
