// Author: Milan Dierick
// Created: 04/04/2021 9:10 PM
// Solution: HeirloomEngine

#pragma once
#include "SoundEngine.h"

namespace Heirloom
{
	class SoundService
	{
	public:
		~SoundService();

		static SoundEngine* GetSoundEngine();
		static void Provide(SoundEngine* soundEngine);

	private:
		static SoundEngine* m_SoundEngine;
	};
}
