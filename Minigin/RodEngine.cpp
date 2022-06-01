#include "RodEnginePCH.h"
#include "RodEngine.h"
#include <thread>
#include "SoundSystem.h"
#include "logger_SoundSystem.h"
#include "sdl_SoundSystem.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "ETime.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSCounter.h"
#include "ImguiManager.h"
#include "SceneGraphTest.h"
#include "SoundTest.h"
#include "Animator.h"

//#pragma warning(push, 0)
//#pragma warning(disable:4996)
//#include <steam_api.h>
//#pragma warning (pop)

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::RodEngine::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		580,
		640,
		SDL_WINDOW_OPENGL	
	);

	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

#if _DEBUG
	SoundSLocator::RegisterSoundSystem(new logger_SoundSystem(new sdl_SoundSystem()));
#else
	SoundSLocator::RegisterSoundSystem(new sdl_SoundSystem());
#endif
}

void dae::RodEngine::Cleanup()
{
	SoundSLocator::DestroySoundSystem();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::RodEngine::Run()
{
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = ETime::GetInstance();

	sceneManager.PostLoad();

	sceneManager.Start();

	bool doContinue = true;
	while (doContinue)
	{
		time.Update();

		if (time.IsFixedUpdateReady())
		{
			sceneManager.FixedUpdate();
			time.FixedUpdateCompleted();
		}

		doContinue = input.ProcessInput();

		sceneManager.Update();
		sceneManager.LateUpdate();

		renderer.Render();
	}

	Cleanup();
}
