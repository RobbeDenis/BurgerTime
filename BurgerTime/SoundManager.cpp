#include "SoundManager.h"
#include "BTEvents.h"
#include "SoundSystem.h"

void SoundManager::Notify(int event)
{
	switch (event)
	{
	case BTEvents::PlayerDied:
		SoundSLocator::GetSoundSystem().Play(BTEvents::PlayerDied, m_Volume);
		break;
	default:
		break;
	}
}
