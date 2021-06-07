#include "hlpch.h"
#include "SoundService.h"

#include "NullSoundEngine.h"

namespace Heirloom
{
	SoundEngine* SoundService::m_SoundEngine = new NullSoundEngine();

	SoundService::~SoundService()
	{
		delete m_SoundEngine;
	}

	SoundEngine* SoundService::GetSoundEngine()
	{
		return m_SoundEngine;
	}

	void SoundService::Provide(SoundEngine* soundEngine)
	{
		delete m_SoundEngine;
		m_SoundEngine = soundEngine;
	}
}
