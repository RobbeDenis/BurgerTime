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
	case BTEvents::BurgerWalk:
		SoundSLocator::GetSoundSystem().Play(BTEvents::BurgerWalk, m_Volume);
		break;
	case BTEvents::EnemyDied:
		SoundSLocator::GetSoundSystem().Play(BTEvents::EnemyDied, m_Volume);
		break;	
	case BTEvents::PepperUsed:
		SoundSLocator::GetSoundSystem().Play(BTEvents::PepperUsed, m_Volume);
		break;
	default:
		break;
	}
}
