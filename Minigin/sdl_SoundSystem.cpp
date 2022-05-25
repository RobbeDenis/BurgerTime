#include "RodEnginePCH.h"
#include "sdl_SoundSystem.h"
#include <map>
#include <thread>

#include "SDL_mixer.h"

struct PlaySound
{
	sound_id id;
	float volume;
};

class dae::sdl_SoundSystem::sdl_SoundSystemImpl
{
public:
	sdl_SoundSystemImpl()
		: m_Head{0}
		, m_Tail{0}
	{
		Mix_Init(0);

		int res = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
		if (res < 0)
			std::cout << "Connot open Audio\n" << SDL_GetError();

		m_AudioThread = std::jthread([&, this] {while (m_KeepThreadOpen) { Update(); }});
	}

	~sdl_SoundSystemImpl()
	{
		m_KeepThreadOpen = false;
		m_AudioThread.join();

		Mix_Quit();
	}

	void RegisterSound(const sound_id id, const std::string& file)
	{
		Mix_Chunk* sample;
		const std::string path = m_AudioPath + file;
		sample = Mix_LoadWAV(path.c_str());

		if (!sample)
		{
			std::cout << "sdl_SoundSystem::RegisterSound Unable to load sound\n";
			throw;
		}

		auto ret = m_pSamples.insert(std::pair<sound_id, Mix_Chunk*>{id, sample});

		if (ret.second == false)
			std::cout << "sdl_SoundSystem::RegisterSound Sound was already registered\n";
	};

	// Disable warnings for possible out of range reading in m_Pending
#pragma warning(push, 0)
#pragma warning(disable:6385)
#pragma warning(disable:6386)
	void Play(const sound_id id, const float volume)
	{
		// Make sure no sounds are being overriden
		assert(((m_Tail + 1) % m_MaxPending) != m_Head);

		// If the sound is already in queue
		// Just change the volume of the existing if the new is louder
		for (unsigned int i = m_Head; i != m_Tail; i = (i + 1) % m_MaxPending)
		{
			if (m_Pending[i].id == id)
			{
				m_Pending[i].volume = glm::max(volume, m_Pending[i].volume);
				return;
			}
		}

		m_Pending[m_Tail].id = id;
		m_Pending[m_Tail].volume = volume;
		m_Tail = (m_Tail + 1) % m_MaxPending;
	}
#pragma warning (pop)

	void Update()
	{
		if (m_Head == m_Tail)
			return;

		Mix_Chunk* sample;
		sample = m_pSamples[m_Pending[m_Head].id];

		// clamp volume form 0 to 128
		float min = 0;
		float max = 128;
		float vol = m_Pending[m_Head].volume * 128;
		vol = glm::clamp(vol, min, max);
		sample->volume = (Uint8)vol;

		if (Mix_PlayChannel(-1, sample, 0) == -1)
			std::cout << "sdl_SoundSystem::Play\n" << SDL_GetError() << "\n";

		m_Head = (m_Head + 1) % m_MaxPending;
	}

private:
	std::map<sound_id, Mix_Chunk*> m_pSamples{};
	std::string m_AudioPath = "../Data/Audio/";

	static const unsigned int m_MaxPending = 16;
	PlaySound m_Pending[m_MaxPending]{};
	std::jthread m_AudioThread;

	unsigned int m_Head;
	unsigned int m_Tail;
	
	bool m_KeepThreadOpen = true;
};

dae::sdl_SoundSystem::sdl_SoundSystem()
{
	m_pImpl = new sdl_SoundSystemImpl();
}

dae::sdl_SoundSystem::~sdl_SoundSystem()
{
	delete m_pImpl;
}

void dae::sdl_SoundSystem::Play(const sound_id id, const float volume) 
{
	m_pImpl->Play(id, volume);
}

void dae::sdl_SoundSystem::RegisterSound(const sound_id id, const std::string& file)
{
	m_pImpl->RegisterSound(id, file);
}