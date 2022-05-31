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
#include "PeterPepper.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "SceneGraphTest.h"
#include "SoundTest.h"
#include "Animator.h"

#pragma warning(push, 0)
#pragma warning(disable:4996)
#include <steam_api.h>
#pragma warning (pop)

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

/**
 * Code constructing the scene world starts here
 */
void dae::RodEngine::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto& input = InputManager::GetInstance();
	auto go = std::make_shared<GameObject>();

	// Background
	RenderComponent* pBackgroundRender = go->AddComponent<RenderComponent>();
	pBackgroundRender->SetTexture("BurgerTimeBackground.png");
	pBackgroundRender->SetDst(25.f, 100.f, 530.f, 530.f);
	scene.Add(go);

	// FPS Counter
	go = std::make_shared<GameObject>();
	TextComponent* pTextComponent = go.get()->AddComponent<TextComponent>();
	pTextComponent->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 13), false);
	pTextComponent->SetText("", false);
	pTextComponent->SetColor({ 40, 215, 67 });
	go->AddComponent<RenderComponent>();
	FPSCounter* pFpsCounter = go->AddComponent<FPSCounter>();
	pFpsCounter->UseSmoothing(true);
	go->SetWorldPosition(7, 7);
	scene.Add(go);

	// CREATING PETER PEPPER
	go = std::make_shared<GameObject>();

	PeterPepper* pPeter = go->AddComponent<PeterPepper>();
	go->AddComponent<Animator>();

	RenderComponent* pPeterPepperRender = go->AddComponent<RenderComponent>();
	pPeterPepperRender->SetTexture("BurgertimeSprites.png");

	// Peter pepper
	input.AddControllerCommand({ XBox360Controller::ControllerButton::ButtonRight, ButtonState::Down }, std::make_unique<PeterMoveRight>(pPeter));
	input.AddControllerCommand({ XBox360Controller::ControllerButton::ButtonLeft, ButtonState::Down }, std::make_unique<PeterMoveLeft>(pPeter));
	input.AddControllerCommand({ XBox360Controller::ControllerButton::ButtonUp, ButtonState::Down }, std::make_unique<PeterMoveUpLadder>(pPeter));
	input.AddControllerCommand({ XBox360Controller::ControllerButton::ButtonDown, ButtonState::Down }, std::make_unique<PeterMoveDownLadder>(pPeter));

	input.AddControllerCommand({ XBox360Controller::ControllerButton::ButtonRight, ButtonState::Released }, std::make_unique<PeterStopMove>(pPeter));
	input.AddControllerCommand({ XBox360Controller::ControllerButton::ButtonLeft, ButtonState::Released }, std::make_unique<PeterStopMove>(pPeter));
	input.AddControllerCommand({ XBox360Controller::ControllerButton::ButtonUp, ButtonState::Released }, std::make_unique<PeterStopMove>(pPeter));
	input.AddControllerCommand({ XBox360Controller::ControllerButton::ButtonDown, ButtonState::Released }, std::make_unique<PeterStopMove>(pPeter));

	go->SetWorldPosition(150, 150);

	scene.Add(go);

	//// Player 1
	//// Creating Peter Pepper UI
	//// Lives
	//go = std::make_shared<GameObject>();
	//go->AddComponent<RenderComponent>();
	//LivesComponent* peterLives = go->AddComponent<LivesComponent>();
	//TextComponent* pTextLives = go->AddComponent<TextComponent>();
	//pTextLives->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	//pTextLives->SetColor({ 233, 252, 62 }, false);
	//go->SetWorldPosition(30, 350);
	//scene.Add(go);

	//// Score
	//go = std::make_shared<GameObject>();
	//go->AddComponent<RenderComponent>();
	//ScoreComponent* peterScore = go->AddComponent<ScoreComponent>();
	//TextComponent* pTextScore = go->AddComponent<TextComponent>();
	//pTextScore->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	//pTextScore->SetColor({ 233, 252, 62 }, false);
	//go->SetWorldPosition(30, 370);
	//scene.Add(go);

	//// Creating Peter Pepper
	//go = std::make_shared<GameObject>();
	//PeterPepper* peter = go->AddComponent<PeterPepper>();
	//peter->AddObserver(peterLives);
	//peter->AddObserver(peterScore);
	//scene.Add(go);

	//// Player 2
	//// Creating Peter Pepper UI
	//// Lives
	//go = std::make_shared<GameObject>();
	//go->AddComponent<RenderComponent>();
	//LivesComponent* peterLives2 = go->AddComponent<LivesComponent>();
	//TextComponent* pTextLives2 = go->AddComponent<TextComponent>();
	//pTextLives2->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	//pTextLives2->SetColor({ 62, 252, 233 }, false);
	//go->SetWorldPosition(30, 410);
	//scene.Add(go);

	//// Score
	//go = std::make_shared<GameObject>();
	//go->AddComponent<RenderComponent>();
	//ScoreComponent* peterScore2 = go->AddComponent<ScoreComponent>();
	//TextComponent* pTextScore2 = go->AddComponent<TextComponent>();
	//pTextScore2->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	//pTextScore2->SetColor({ 62, 252, 233 }, false);
	//go->SetWorldPosition(30, 430);
	//scene.Add(go);

	//// Creating Peter Pepper
	//go = std::make_shared<GameObject>();
	//PeterPepper* peter2 = go->AddComponent<PeterPepper>();
	//peter2->SetPlayer(false);// FOR TESTING ASSIGNMENT
	//peter2->AddObserver(peterLives2);
	//peter2->AddObserver(peterScore2);
	//scene.Add(go);

	//// Inputs explenation
	//std::cout << "\n\nPlayer 1:" <<
	//	"\n\t* Die: DpadDown" <<
	//	"\n\t* Kill enemy: DpadRight" <<
	//	"\n\t* Burger fall: DpadLeft" <<
	//	"\nPlayer 2:" <<
	//	"\n\t* Die: ButtonA" <<
	//	"\n\t* Kill enemy: ButtonB" <<
	//	"\n\t* Burger fall: ButtonX\n\n" << std::endl;

	//// Scenegraph Test
	//go = std::make_shared<GameObject>("IAmParent");
	//go->AddComponent<SceneGraphTest>();
	//go->AddChild("Child0");
	//go->AddChild("Child1");
	//go->AddChild("Child2");
	//go->AddChild("Child3");

	//scene.Add(go);

	////Sound test
	//go = std::make_shared<GameObject>();
	//go->AddComponent<SoundTest>();
	//scene.Add(go);
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
	Initialize();

	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();
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

			SteamAPI_RunCallbacks();

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
	}

	Cleanup();
}
