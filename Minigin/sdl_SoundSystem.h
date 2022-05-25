#pragma once
#include "SoundSystem.h"

namespace dae
{
	class sdl_SoundSystem final : public SoundSystem
	{
	public:
		sdl_SoundSystem();
		~sdl_SoundSystem();

		void Play(const sound_id id, const float volume) override;
		void RegisterSound(const sound_id, const std::string&) override;

	private:
		class sdl_SoundSystemImpl;
		sdl_SoundSystemImpl* m_pImpl;
	};
}

