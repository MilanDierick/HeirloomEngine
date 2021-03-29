// Author: Milan Dierick
// Created: 28/03/2021 7:21 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Audio/SoundEngine.h"
#include "Heirloom/Core/LockFreeStack.h"
#include <irrKlang.h>

namespace Heirloom
{
	class SimpleSoundEngine final : public SoundEngine
	{
	public:
		[[nodiscard]] SimpleSoundEngine();
		~SimpleSoundEngine();

		void Update() override;
		void Play(Ref<Sound> sound) override;
		void Stop(Ref<Sound> sound) override;
		void StopAll() override;

	private:
		void SwapBuffers();

		irrklang::ISoundEngine* m_SoundEngine;
		
		LockFreeStack<Sound> m_SoundsQueue;
		LockFreeStack<Sound> m_SoundsQueueBuffer;
	};
}
