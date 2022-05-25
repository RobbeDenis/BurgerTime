#pragma once

using sound_id = unsigned int;

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(const sound_id id, const float volume) = 0;
	virtual void RegisterSound(const sound_id id, const std::string& path) = 0;
};

class null_SoundSystem final : public SoundSystem
{
	void Play(const sound_id, const float) override {};
	void RegisterSound(const sound_id, const std::string&) override {};
};

class SoundSLocator final
{
private:
	static SoundSystem* _ss_instance;
	static null_SoundSystem _default_ss;

public:
	static void DestroySoundSystem() { delete _ss_instance; };
	static SoundSystem& GetSoundSystem() { return *_ss_instance; };
	static void RegisterSoundSystem(SoundSystem* ss) 
	{ 
		if (ss == nullptr)
			_ss_instance = &_default_ss;
		else
			_ss_instance = ss; 
	};
};
