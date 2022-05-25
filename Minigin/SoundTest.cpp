#include "RodEnginePCH.h"
#include "SoundTest.h"
#include "SoundSystem.h"
#include "InputManager.h"

enum Drums
{
	Kick = 10,
	Snare = 11,
	HiHat = 12
};

void dae::SoundTest::PostLoad()
{
	std::cout << "\nStart sound test\n\n";

	SoundSLocator::GetSoundSystem().RegisterSound(Drums::Kick, "Kick.wav");
	SoundSLocator::GetSoundSystem().RegisterSound(Drums::Snare, "Snare.wav");
	SoundSLocator::GetSoundSystem().RegisterSound(Drums::HiHat, "HiHat.wav");

	// PRE EVENT QUEUE

	//std::cout << "-- Beat 3 different sounds --\n\n";
	//float beatVolume = 0.2f;
	//for (int i = 0; i < 2; i++)
	//{
	//	SoundSLocator::GetSoundSystem().Play(Drums::Kick, beatVolume);
	//	Sleep(200);
	//	SoundSLocator::GetSoundSystem().Play(Drums::HiHat, beatVolume);
	//	Sleep(200);
	//	SoundSLocator::GetSoundSystem().Play(Drums::Snare, beatVolume);
	//	Sleep(200);
	//	SoundSLocator::GetSoundSystem().Play(Drums::HiHat, beatVolume);
	//	Sleep(200);
	//}

	//std::cout << "\n-- Volume Test --\n\n";

	//for (float volume = -0.2f; volume < 1.2f; volume += 0.05f)
	//{
	//	SoundSLocator::GetSoundSystem().Play(Drums::Kick, volume);
	//	Sleep(100);
	//}

	InputManager::GetInstance().AddController(0);
}

void dae::SoundTest::Update()
{
	if (m_FirstFrame)
	{
		SoundSLocator::GetSoundSystem().Play(Drums::Kick, 0.5f);

		SoundSLocator::GetSoundSystem().Play(Drums::HiHat, 0.5f);

		SoundSLocator::GetSoundSystem().Play(Drums::Snare, 0.5f);
		SoundSLocator::GetSoundSystem().Play(Drums::Snare, 0.1f);
		SoundSLocator::GetSoundSystem().Play(Drums::Snare, 0.8f);

		std::cout << "\n---- Use controller to trigger sounds ----\n" <<
					"ButtonA: Kick\nButtonB: HiHat\nButtonX: Snare\nButtonUp: Volume up\nButtonDown: Volume Down\n\n";

		m_FirstFrame = false;
	}

	if(InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonA, 0))
		SoundSLocator::GetSoundSystem().Play(Drums::Kick, m_Volume);

	if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonB, 0))
		SoundSLocator::GetSoundSystem().Play(Drums::HiHat, m_Volume);

	if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonX, 0))
		SoundSLocator::GetSoundSystem().Play(Drums::Snare, m_Volume);


	if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonUp, 0))
	{
		m_Volume += 0.1f;
		std::cout << "Volume: " << m_Volume << "\n";
	}

	if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonDown, 0))
	{
		m_Volume -= 0.1f;
		std::cout << "Volume: " << m_Volume << "\n";
	}
}
