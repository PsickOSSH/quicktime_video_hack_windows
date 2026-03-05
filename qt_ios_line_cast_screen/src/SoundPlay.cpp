#include "SoundPlay.h"

bool SoundPlay::Init()
{
    m_AudioSpec.freq        = 0;
    m_AudioSpec.format      = AUDIO_S16SYS;
    m_AudioSpec.channels    = 0;
    m_AudioSpec.silence     = 0;
    m_AudioSpec.samples     = 0;
    m_AudioSpec.padding     = 0;
    m_AudioSpec.size        = 0;
    m_AudioSpec.callback    = nullptr;
    m_AudioSpec.userdata    = nullptr;
    
	if (SDL_Init(SDL_INIT_AUDIO)) 
	{
		return false;
	}
    return true;
}

void SoundPlay::UnInit()
{

}

void SoundPlay::PauseAudioDevice(int nPauseOn)
{
    SDL_PauseAudioDevice(m_AudioDeviceID, nPauseOn);
}

bool SoundPlay::SetFormat(int nChannels, int nSamplerate)
{
	SDL_zero(m_AudioSpec);
	m_AudioSpec.freq		= nSamplerate;
	m_AudioSpec.format		= AUDIO_S16SYS;
	m_AudioSpec.channels	= nChannels;
	m_AudioSpec.samples		= 4096;
	//m_AudioSpec.silence		= 0;
	m_AudioSpec.callback	= nullptr;

	m_AudioDeviceID = SDL_OpenAudioDevice(nullptr, 0, &m_AudioSpec, nullptr, 0);
	if (m_AudioDeviceID < 2)
	{
		return false;
	}
	SDL_PauseAudioDevice(m_AudioDeviceID, 0);
	return true;
}

void SoundPlay::PushData(void* pBuffer, int nBuffLeng)
{
    //	unsigned char *pTmpBuffer = (unsigned char*)malloc(nBuffLeng);
    //	if (!pTmpBuffer) return;
    //	memcpy(pTmpBuffer, (const Uint8*)pBuffer, nBuffLeng);
    //	SDL_QueueAudio(m_AudioDeviceID, pTmpBuffer, nBuffLeng);
    //	free(pTmpBuffer);

    SDL_QueueAudio(m_AudioDeviceID, pBuffer, nBuffLeng);
}
