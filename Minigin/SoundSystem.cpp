#include "RodEnginePCH.h"
#include "SoundSystem.h"

null_SoundSystem SoundSLocator::_default_ss{};
SoundSystem* SoundSLocator::_ss_instance = &_default_ss;