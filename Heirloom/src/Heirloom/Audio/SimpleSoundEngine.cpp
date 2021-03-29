#include "hlpch.h"
#include "SimpleSoundEngine.h"

Heirloom::SimpleSoundEngine::SimpleSoundEngine() : SoundEngine()
{
	m_SoundEngine = irrklang::createIrrKlangDevice();

	m_SoundEngine->play2D("assets/sounds/breakout.mp3", true);
}

Heirloom::SimpleSoundEngine::~SimpleSoundEngine()
{
	m_SoundEngine->drop();
}

void Heirloom::SimpleSoundEngine::Update()
{
	SwapBuffers();
}

void Heirloom::SimpleSoundEngine::Play(Ref<Sound> sound)
{
	
}

void Heirloom::SimpleSoundEngine::Stop(Ref<Sound> sound)
{
	
}

void Heirloom::SimpleSoundEngine::StopAll()
{
	
}

void Heirloom::SimpleSoundEngine::SwapBuffers()
{
	
}
