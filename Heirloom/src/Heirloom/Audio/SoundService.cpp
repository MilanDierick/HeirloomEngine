#include "hlpch.h"
#include "SoundService.h"

#include "NullSoundEngine.h"

Heirloom::SoundEngine* Heirloom::SoundService::m_SoundEngine = new NullSoundEngine();
