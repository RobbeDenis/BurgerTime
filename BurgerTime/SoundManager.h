#pragma once
#include <Observer.h>
#include <BaseComponent.h>

class SoundManager final : public dae::Observer
{
public:
	void Notify(int) override;
	void Notify(dae::BaseComponent*, int event) override { Notify(event); };
	void SetVolume(const float volume) { m_Volume = volume; };

private:
	float m_Volume = 0.5f;
};

