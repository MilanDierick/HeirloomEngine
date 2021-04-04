#include "hlpch.h"
#include "NullSoundEngine.h"

void Heirloom::NullSoundEngine::Update()
{
	
}

void Heirloom::NullSoundEngine::Play(const Ref<Sound> sound)
{
	HL_CORE_TRACE("NullSoundEngine started playing sound \"{0}\"", sound->FileName);
}

void Heirloom::NullSoundEngine::Play(const std::string filePath)
{
	HL_CORE_TRACE("NullSoundEngine started playing sound \"{0}\"", filePath);
}

void Heirloom::NullSoundEngine::Stop(const Ref<Sound> sound)
{
	HL_CORE_TRACE("NullSoundEngine stopped playing sound \"{0}\"", sound->FileName);
}

void Heirloom::NullSoundEngine::StopAll()
{
	HL_CORE_TRACE("NullSoundEngine stopped playing all sounds");
}
