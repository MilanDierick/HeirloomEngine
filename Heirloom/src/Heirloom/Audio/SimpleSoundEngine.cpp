#include "hlpch.h"
#include "SimpleSoundEngine.h"

Heirloom::SimpleSoundEngine::SimpleSoundEngine() : SoundEngine()
{
	HL_PROFILE_FUNCTION()

	m_SoundEngine = irrklang::createIrrKlangDevice();

	// m_SoundEngine->play2D("assets/sounds/breakout.mp3");

	m_SoundsQueue       = new LockFreeStack<Ref<Sound>>();
	m_SoundsQueueBuffer = new LockFreeStack<Ref<Sound>>();
}

Heirloom::SimpleSoundEngine::~SimpleSoundEngine()
{
	HL_PROFILE_FUNCTION()

	m_SoundEngine->drop();

	delete m_SoundsQueue;
	delete m_SoundsQueueBuffer;
}

void Heirloom::SimpleSoundEngine::Update()
{
	HL_PROFILE_FUNCTION()

	SwapBuffers();
	PlayBufferedSounds();
}

void Heirloom::SimpleSoundEngine::Play(std::string filePath)
{
	HL_PROFILE_FUNCTION()

	m_SoundsQueue->Push(CreateRef<Sound>(filePath, 1.0f, false));
}

void Heirloom::SimpleSoundEngine::Play(const Ref<Sound> sound)
{
	HL_PROFILE_FUNCTION()

	m_SoundsQueue->Push(sound);
}

void Heirloom::SimpleSoundEngine::Stop(const Ref<Sound> sound)
{
	for (std::vector<irrklang::ISoundSource*>::value_type soundSource : m_CachedSoundSources)
	{
		if (sound->FileName == soundSource->getName())
		{
			m_SoundEngine->stopAllSoundsOfSoundSource(soundSource);
		}
	}
}

void Heirloom::SimpleSoundEngine::StopAll()
{
	HL_PROFILE_FUNCTION()

	m_SoundEngine->stopAllSounds();
}

void Heirloom::SimpleSoundEngine::SwapBuffers()
{
	HL_PROFILE_FUNCTION()

	std::swap(m_SoundsQueue, m_SoundsQueueBuffer);
}

void Heirloom::SimpleSoundEngine::CacheSound(irrklang::ISoundSource* soundSource)
{
	HL_PROFILE_FUNCTION()

	bool soundSourceFound = false;

	for (std::vector<irrklang::ISoundSource*>::value_type cachedSoundSource : m_CachedSoundSources)
	{
		if (soundSource->getName() == cachedSoundSource->getName())
		{
			soundSourceFound = true;
		}
	}

	if (!soundSourceFound)
	{
		m_CachedSoundSources.push_back(soundSource);
	}
}

void Heirloom::SimpleSoundEngine::PlayBufferedSounds()
{
	HL_PROFILE_FUNCTION()

	if (m_SoundsQueueBuffer->Size() == 0)
	{
		return;
	}

	// TODO: Spawning a new thread every time we want to play a new sound is quite ridiculous, consider spawning a single thread that keeps on emptying the sound buffer
	std::thread thread([this]()
	{
		while (m_SoundsQueueBuffer->Size() != 0)
		{
			Node<Ref<Sound>>* node = m_SoundsQueueBuffer->Pop();

			irrklang::ISoundSource* result = m_SoundEngine->play2D(node->Value->FileName.c_str(),
			                                                       node->Value->ShouldLoop, false, true)->
			                                                getSoundSource();

			CacheSound(result);
			delete node;
		}
	});

	thread.detach();
}
