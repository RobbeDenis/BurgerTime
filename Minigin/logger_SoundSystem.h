#pragma once
#include "SoundSystem.h"
class logger_SoundSystem final : public SoundSystem
{
private:
	SoundSystem* _real_ss;

public:
	logger_SoundSystem(SoundSystem* ss) : _real_ss(ss) {};
	~logger_SoundSystem() { delete _real_ss; };

	void Play(const sound_id id, const float volume) override
	{
		_real_ss->Play(id, volume);
		std::cout << "SSLogger: playing " << id << " at volume " << volume << "\n";
	}

	void RegisterSound(const sound_id id, const std::string& path) override
	{
		_real_ss->RegisterSound(id, path);
	}
};

