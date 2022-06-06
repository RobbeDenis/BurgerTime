// BurgerTime.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <RodEngine.h>
#include <SceneManager.h>
#include <InputManager.h>
#include <RenderComponent.h>
#include <Scene.h>
#include <TextComponent.h>
#include <ResourceManager.h>
#include <FPSCounter.h>
#include <Animator.h>
#include <Collider.h>
#include <DebugRenderComponent.h>
#include <SoundSystem.h>

#include "PeterPepper.h"
#include "BurgerTimeCommands.h"
#include "Platform.h"
#include "Ladder.h"
#include "BurgerPart.h"
#include "Plate.h"
#include "ScoreComponent.h"
#include "LivesComponent.h"
#include "Enemy.h"
#include "HotdogController.h"
#include "PickleController.h"
#include "PepperCloud.h"
#include "PepperUI.h"
#include "SoundManager.h"
#include "BTEvents.h"
#include "GameManager.h"
#include "UIPointer.h"

void LoadGame(GameManager* pGame, SoundManager* pSoundManager);

void CreateStartMenu(GameManager* pGame, SoundManager* pSoundManager);
void CreateSinglePlayer(GameManager* pGame, SoundManager* pSoundManager);
void CreateCoop(GameManager* pGame, SoundManager* pSoundManager);
void CreateVersus(GameManager* pGame, SoundManager* pSoundManager);

void LoadLevel(dae::Scene& scene, dae::Observer* pGame, dae::Observer* scoreComp, dae::Observer* pSoundManager, Character* target);

std::shared_ptr<dae::GameObject> CreateBackground(const std::string& texture);
std::shared_ptr<dae::GameObject> CreateFPSCounter(const glm::vec3& pos, const SDL_Color& color);
std::shared_ptr<dae::GameObject> CreateScoreUI(const glm::vec3& pos, const SDL_Color& scoreColor, const SDL_Color& textColor);
std::shared_ptr<dae::GameObject> CreatePepperCountUI(const glm::vec3& pos, const SDL_Color& pepperColor);
std::shared_ptr<dae::GameObject> CreateLivesUI(const glm::vec3& pos, const std::string& texture);
std::shared_ptr<dae::GameObject> CreatePlayerCharacter(const glm::vec3& pos, const std::string& texture, dae::Observer* pGame, dae::Observer* score, dae::Observer* pSoundManager, dae::Observer* lives, dae::Observer* pepperUI, PepperCloud* cloud);
std::shared_ptr<dae::GameObject> CreatePepperCloud();

std::shared_ptr<dae::GameObject> CreatePlatform(const int platformWidth, const glm::vec3& pos);
std::shared_ptr<dae::GameObject> CreateLadder(const int ladderHeight, const glm::vec3& pos);
std::shared_ptr<dae::GameObject> CreateBurgerPart(dae::Observer* score, const glm::vec3& pos, const PartType type);
std::shared_ptr<dae::GameObject> CreatePlate(const glm::vec3& pos);
std::shared_ptr<dae::GameObject> CreateEnemy(dae::Observer* pGame, dae::Observer* score, dae::Observer* pSoundManager, Character* target, const glm::vec3& pos, const EnemyType type);

int main(int, char* []) 
{
	dae::RodEngine engine;

	engine.Initialize();

	dae::ResourceManager::GetInstance().Init("../Data/");
	dae::InputManager::GetInstance().AddController(0);

	SoundManager* pSoundManager = new SoundManager();
	GameManager* pGame = new GameManager();

	LoadGame(pGame, pSoundManager);

	engine.Run();

	delete pSoundManager;
	delete pGame;

	return 0;
}

void LoadGame(GameManager* pGame, SoundManager* pSoundManager)
{
	pSoundManager->SetVolume(0.1f);
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::PlayerDied, "LoseLife.mp3");
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::BurgerWalk, "BurgerWalk.wav");
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::EnemyDied, "EnemyDied.wav");
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::PepperUsed, "Attack.wav");
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::BurgerDropped, "Bounce.wav");
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::UIIndexChanged, "Click.wav");

	CreateSinglePlayer(pGame, pSoundManager);
	CreateCoop(pGame, pSoundManager);
	CreateVersus(pGame, pSoundManager);
	CreateStartMenu(pGame, pSoundManager);

	dae::SceneManager::GetInstance().SetScene("StartMenu");
	//dae::SceneManager::GetInstance().SetScene("SinglePlayer");
	//dae::SceneManager::GetInstance().SetScene("Coop");
	//dae::SceneManager::GetInstance().SetScene("Versus");
}

void CreateStartMenu(GameManager* pGame, SoundManager* pSoundManager)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(pGame->GetStartMenuName());
	auto& input = dae::InputManager::GetInstance();

	// Adding GameObjects
	std::shared_ptr<dae::GameObject> go;

	// Add background
	scene.Add(go = CreateBackground("StartMenu.jpg"));

	// FPS Counter
	scene.Add(CreateFPSCounter({ 7.f, 7.f, 0.f }, { 40, 215, 67 }));

	// Adding pointer
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	auto* p = go->AddComponent<UIPointer>();
	p->SetMax(3);
	p->AddObserver(pSoundManager);
	p->AddObserver(pGame);
	go->SetWorldPosition({ 175, 310,0 });

	scene.Add(go);

	input.AddKeyboardCommand({ SDL_SCANCODE_UP, dae::ButtonState::Pressed }, std::make_unique<PointerUp>(p), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_DOWN, dae::ButtonState::Pressed }, std::make_unique<PointerDown>(p), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_SPACE, dae::ButtonState::Pressed }, std::make_unique<Confirmed>(p), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Pressed }, std::make_unique<PointerUp>(p), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Pressed }, std::make_unique<PointerDown>(p), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonA, dae::ButtonState::Pressed }, std::make_unique<Confirmed>(p), scene.GetIndex());
}

void CreateSinglePlayer(GameManager* pGame, SoundManager* pSoundManager)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(pGame->GetSinglePlayerName());
	auto& input = dae::InputManager::GetInstance();

	scene.EnableDebugRender(false);

	// Adding GameObjects
	std::shared_ptr<dae::GameObject> go;

	// Background
	scene.Add(go = CreateBackground("BurgerTimeBackground.png"));

	// FPS Counter
	scene.Add(CreateFPSCounter({ 7.f, 7.f, 0.f }, { 40, 215, 67 }));

	// Score component
	scene.Add(go = CreateScoreUI({40.f, 23.f, 0.f}, { 255, 255, 255 }, { 255, 0, 0 }));
	ScoreComponent* score = go->GetComponent<ScoreComponent>();

	// Pepper count
	scene.Add(go = CreatePepperCountUI({ 550, 23, 0 }, { 255, 255, 255 }));
	PepperUI* pepperUI = go->GetComponent<PepperUI>();

	// Lives
	scene.Add(go = CreateLivesUI({ 5,640,0 }, "BurgertimeSprites.png"));
	LivesComponent* lives = go->GetComponent<LivesComponent>();

	// Creating pepper cloud
	scene.Add(go = CreatePepperCloud());
	PepperCloud* cloud = go->GetComponent<PepperCloud>();

	// CREATING PETER PEPPER
	scene.Add(go = CreatePlayerCharacter({ 10, 500, 0 }, "BurgertimeSprites.png", pGame, score, lives, pepperUI, pSoundManager, cloud));
	PeterPepper* pPeter = go->GetComponent<PeterPepper>();

	// KEYBOARD INPUTS
	input.AddKeyboardCommand({ SDL_SCANCODE_RIGHT, dae::ButtonState::Down }, std::make_unique<IMoveRight>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_LEFT, dae::ButtonState::Down }, std::make_unique<IMoveLeft>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_UP, dae::ButtonState::Down }, std::make_unique<IMoveUpLadder>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_DOWN, dae::ButtonState::Down }, std::make_unique<IMoveDownLadder>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_RIGHT, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_LEFT, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_UP, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_DOWN, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_X, dae::ButtonState::Pressed }, std::make_unique<IUseAbility>(pPeter), scene.GetIndex());

	// CONTROLLER INPUTS
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Down }, std::make_unique<IMoveRight>(pPeter), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Down }, std::make_unique<IMoveLeft>(pPeter), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Down }, std::make_unique<IMoveUpLadder>(pPeter), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Down }, std::make_unique<IMoveDownLadder>(pPeter), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonA, dae::ButtonState::Pressed }, std::make_unique<IUseAbility>(pPeter), scene.GetIndex());

	//Load level
	LoadLevel(scene, pGame, score, pSoundManager, pPeter);
}

void CreateCoop(GameManager* pGame, SoundManager* pSoundManager)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(pGame->GetCoopName());
	auto& input = dae::InputManager::GetInstance();

	scene.EnableDebugRender(false);

	// Adding GameObjects
	std::shared_ptr<dae::GameObject> go;

	// Background
	scene.Add(go = CreateBackground("BurgerTimeBackground.png"));

	// FPS Counter
	scene.Add(CreateFPSCounter({ 7.f, 7.f, 0.f }, { 40, 215, 67 }));

	// Score component
	scene.Add(go = CreateScoreUI({ 40.f, 23.f, 0.f }, { 255, 255, 255 }, { 255, 0, 0 }));
	ScoreComponent* score = go->GetComponent<ScoreComponent>();

	// Pepper count
	scene.Add(go = CreatePepperCountUI({ 550, 23, 0 }, { 255, 255, 255 }));
	PepperUI* pepperUI = go->GetComponent<PepperUI>();

	// Lives
	scene.Add(go = CreateLivesUI({ 5,640,0 }, "BurgertimeSprites.png"));
	LivesComponent* lives = go->GetComponent<LivesComponent>();

	// Creating pepper cloud
	scene.Add(go = CreatePepperCloud());
	PepperCloud* cloudPepper = go->GetComponent<PepperCloud>();

	// Creating salt cloud
	scene.Add(go = CreatePepperCloud());
	PepperCloud* cloudSalt = go->GetComponent<PepperCloud>();

	// CREATING PETER PEPPER
	scene.Add(go = CreatePlayerCharacter({ 10, 500, 0 }, "BurgertimeSprites.png", pGame, score, lives, pepperUI, pSoundManager, cloudPepper));
	PeterPepper* pPepper = go->GetComponent<PeterPepper>();

	// KEYBOARD INPUTS
	input.AddKeyboardCommand({ SDL_SCANCODE_RIGHT, dae::ButtonState::Down }, std::make_unique<IMoveRight>(pPepper), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_LEFT, dae::ButtonState::Down }, std::make_unique<IMoveLeft>(pPepper), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_UP, dae::ButtonState::Down }, std::make_unique<IMoveUpLadder>(pPepper), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_DOWN, dae::ButtonState::Down }, std::make_unique<IMoveDownLadder>(pPepper), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_RIGHT, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPepper), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_LEFT, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPepper), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_UP, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPepper), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_DOWN, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPepper), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_X, dae::ButtonState::Pressed }, std::make_unique<IUseAbility>(pPepper), scene.GetIndex());

	// CREATING SALT
	scene.Add(go = CreatePlayerCharacter({ 200, 500, 0 }, "Salt.png", pGame, score, lives, pepperUI, pSoundManager, cloudSalt));
	PeterPepper* pSalt = go->GetComponent<PeterPepper>();

	// CONTROLLER INPUTS
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Down }, std::make_unique<IMoveRight>(pSalt), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Down }, std::make_unique<IMoveLeft>(pSalt), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Down }, std::make_unique<IMoveUpLadder>(pSalt), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Down }, std::make_unique<IMoveDownLadder>(pSalt), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Released }, std::make_unique<IStopMove>(pSalt), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Released }, std::make_unique<IStopMove>(pSalt), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Released }, std::make_unique<IStopMove>(pSalt), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Released }, std::make_unique<IStopMove>(pSalt), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonA, dae::ButtonState::Pressed }, std::make_unique<IUseAbility>(pSalt), scene.GetIndex());

	//Load level
	LoadLevel(scene, pGame, score, pSoundManager, pPepper);
}

void CreateVersus(GameManager* pGame, SoundManager* pSoundManager)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(pGame->GetVersusName());
	auto& input = dae::InputManager::GetInstance();

	scene.EnableDebugRender(false);

	// Adding GameObjects
	std::shared_ptr<dae::GameObject> go;

	// Background
	scene.Add(go = CreateBackground("BurgerTimeBackground.png"));

	// FPS Counter
	scene.Add(CreateFPSCounter({ 7.f, 7.f, 0.f }, { 40, 215, 67 }));

	// Score component
	scene.Add(go = CreateScoreUI({ 40.f, 23.f, 0.f }, { 255, 255, 255 }, { 255, 0, 0 }));
	ScoreComponent* score = go->GetComponent<ScoreComponent>();

	// Pepper count
	scene.Add(go = CreatePepperCountUI({ 550, 23, 0 }, { 255, 255, 255 }));
	PepperUI* pepperUI = go->GetComponent<PepperUI>();

	// Lives
	scene.Add(go = CreateLivesUI({ 5,640,0 }, "BurgertimeSprites.png"));
	LivesComponent* lives = go->GetComponent<LivesComponent>();

	// Creating pepper cloud
	scene.Add(go = CreatePepperCloud());
	PepperCloud* cloud = go->GetComponent<PepperCloud>();

	// CREATING PETER PEPPER
	scene.Add(go = CreatePlayerCharacter({ 10, 500, 0 }, "BurgertimeSprites.png", pGame, score, lives, pepperUI, pSoundManager, cloud));
	PeterPepper* pPeter = go->GetComponent<PeterPepper>();

	// KEYBOARD INPUTS
	input.AddKeyboardCommand({ SDL_SCANCODE_RIGHT, dae::ButtonState::Down }, std::make_unique<IMoveRight>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_LEFT, dae::ButtonState::Down }, std::make_unique<IMoveLeft>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_UP, dae::ButtonState::Down }, std::make_unique<IMoveUpLadder>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_DOWN, dae::ButtonState::Down }, std::make_unique<IMoveDownLadder>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_RIGHT, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_LEFT, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_UP, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_DOWN, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter), scene.GetIndex());
	input.AddKeyboardCommand({ SDL_SCANCODE_X, dae::ButtonState::Pressed }, std::make_unique<IUseAbility>(pPeter), scene.GetIndex());

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<dae::Collider>()->SetLabel("Enemy");
	go->AddComponent<dae::DebugRenderComponent>();
	go->AddComponent<dae::RenderComponent>()->SetTexture("BurgertimeSprites.png");
	auto hotdog = go->AddComponent<Enemy>();
	hotdog->SetType(EnemyType::HotDog);
	hotdog->SetValue(100);
	hotdog->AddObserver(score);
	hotdog->AddObserver(pSoundManager);
	go->SetWorldPosition({ 400.f, 120.f, 0.f });
	scene.Add(go);

	// CONTROLLER INPUTS
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Down }, std::make_unique<IMoveRight>(hotdog), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Down }, std::make_unique<IMoveLeft>(hotdog), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Down }, std::make_unique<IMoveUpLadder>(hotdog), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Down }, std::make_unique<IMoveDownLadder>(hotdog), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Released }, std::make_unique<IStopMove>(hotdog), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Released }, std::make_unique<IStopMove>(hotdog), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Released }, std::make_unique<IStopMove>(hotdog), scene.GetIndex());
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Released }, std::make_unique<IStopMove>(hotdog), scene.GetIndex());

	//Load level
	LoadLevel(scene, pGame, score, pSoundManager, pPeter);
}

void LoadLevel(dae::Scene& scene, dae::Observer* pGame, dae::Observer* scoreComp, dae::Observer* pSoundManager, Character* target)
{
	// Adding Ladders
	// First row
	scene.Add(CreateLadder(90, { 36.f, 135.f, 0.f }));
	scene.Add(CreateLadder(385, { 158.f, 135.f, 0.f }));
	scene.Add(CreateLadder(130, { 219.f, 135.f, 0.f }));
	scene.Add(CreateLadder(385, { 280.f, 135.f, 0.f }));
	scene.Add(CreateLadder(385, { 402.f, 135.f, 0.f }));
	scene.Add(CreateLadder(173, { 525.f, 135.f, 0.f }));
	// Second row
	scene.Add(CreateLadder(215, { 96.f, 221.f, 0.f }));
	scene.Add(CreateLadder(130, { 341.f, 221.f, 0.f }));
	// Third row
	scene.Add(CreateLadder(213, { 36.f, 306.f, 0.f }));
	scene.Add(CreateLadder(213, { 463.f, 306.f, 0.f }));
	// Forth row
	scene.Add(CreateLadder(128, { 524.f, 390.f, 0.f }));

	// Adding platforms
	// Row 1
	scene.Add(CreatePlatform(530, { 25.f, 133.f, 0.f }));
	// Row 2
	scene.Add(CreatePlatform(163, { 25.f, 218.f, 0.f }));
	scene.Add(CreatePlatform(285, { 270.f, 218.f, 0.f }));
	// Row 3
	scene.Add(CreatePlatform(164, { 147.f, 260.f, 0.f }));
	// Row 4
	scene.Add(CreatePlatform(163, { 25.f, 302.f, 0.f }));
	scene.Add(CreatePlatform(163, { 392.f, 302.f, 0.f }));
	// Row 5
	scene.Add(CreatePlatform(285, { 148.f, 344.f, 0.f }));
	// Row 6
	scene.Add(CreatePlatform(165, { 392.f, 387.f, 0.f }));
	// Row 7
	scene.Add(CreatePlatform(410, { 24.f, 430.f, 0.f }));
	// Row 8
	scene.Add(CreatePlatform(530, { 25.f, 514.f, 0.f }));

	// Adding Burger parts
	// Colum 1
	scene.Add(CreateBurgerPart(scoreComp, { 67.f, 125.f, 0.f }, PartType::TopBun));
	scene.Add(CreateBurgerPart(scoreComp, { 67.f, 211.f, 0.f }, PartType::Lettuce));
	scene.Add(CreateBurgerPart(scoreComp, { 67.f, 295.f, 0.f }, PartType::Patty));
	scene.Add(CreateBurgerPart(scoreComp, { 67.f, 507.f, 0.f }, PartType::BotBun));
	// Colum 2
	scene.Add(CreateBurgerPart(scoreComp, { 190.f, 253.f, 0.f }, PartType::TopBun));
	scene.Add(CreateBurgerPart(scoreComp, { 190.f, 337.f, 0.f }, PartType::Lettuce));
	scene.Add(CreateBurgerPart(scoreComp, { 190.f, 423.f, 0.f }, PartType::Patty));
	scene.Add(CreateBurgerPart(scoreComp, { 190.f, 507.f, 0.f }, PartType::BotBun));
	// Colum 3
	scene.Add(CreateBurgerPart(scoreComp, { 312.f, 125.f, 0.f }, PartType::TopBun));
	scene.Add(CreateBurgerPart(scoreComp, { 312.f, 211.f, 0.f }, PartType::Lettuce));
	scene.Add(CreateBurgerPart(scoreComp, { 312.f, 337.f, 0.f }, PartType::Patty));
	scene.Add(CreateBurgerPart(scoreComp, { 312.f, 507.f, 0.f }, PartType::BotBun));
	// Colum 4
	scene.Add(CreateBurgerPart(scoreComp, { 435.f, 125.f, 0.f }, PartType::TopBun));
	scene.Add(CreateBurgerPart(scoreComp, { 435.f, 211.f, 0.f }, PartType::Lettuce));
	scene.Add(CreateBurgerPart(scoreComp, { 435.f, 295.f, 0.f }, PartType::Patty));
	scene.Add(CreateBurgerPart(scoreComp, { 435.f, 380.f, 0.f }, PartType::BotBun));

	// Add plates
	scene.Add(CreatePlate({ 92.f, 548.f, 0.f }));
	scene.Add(CreatePlate({ 220.f, 548.f, 0.f }));
	scene.Add(CreatePlate({ 350.f, 548.f, 0.f }));
	scene.Add(CreatePlate({ 450.f, 548.f, 0.f }));

	// Adding hot dogs
	scene.Add(CreateEnemy(pGame, scoreComp, pSoundManager, target, { 100.f, 120.f, 0.f }, EnemyType::HotDog));
	scene.Add(CreateEnemy(pGame, scoreComp, pSoundManager, target, { 40.f, 120.f, 0.f }, EnemyType::HotDog));

	// Adding Egg
	scene.Add(CreateEnemy(pGame, scoreComp, pSoundManager, target, { 500.f, 120.f, 0.f }, EnemyType::Egg));

	// Adding Pickle
	scene.Add(CreateEnemy(pGame, scoreComp, pSoundManager, target, { 420.f, 330.f, 0.f }, EnemyType::Pickle));
}

std::shared_ptr<dae::GameObject> CreatePepperCloud()
{
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<PepperCloud>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<dae::Collider>()->SetLabel("Pepper");
	go->AddComponent<dae::DebugRenderComponent>();
	go->AddComponent<dae::RenderComponent>()->SetTexture("BurgertimeSprites.png");

	return go;
}

std::shared_ptr<dae::GameObject> CreatePlayerCharacter(const glm::vec3& pos, const std::string& texture, dae::Observer* pGame, dae::Observer* score, dae::Observer* pSoundManager, dae::Observer* lives, dae::Observer* pepperUI, PepperCloud* cloud)
{
	auto go = std::make_shared<dae::GameObject>();

	PeterPepper* pPeter = go->AddComponent<PeterPepper>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<dae::Collider>()->SetLabel("Player");
	go->AddComponent<dae::DebugRenderComponent>();

	dae::RenderComponent* pPeterPepperRender = go->AddComponent<dae::RenderComponent>();
	pPeterPepperRender->SetTexture(texture);

	pPeter->AddObserver(score);
	pPeter->AddObserver(lives);
	pPeter->AddObserver(pepperUI);
	pPeter->AddObserver(pSoundManager);
	pPeter->AddObserver(pGame);
	pPeter->AddPepperCloud(cloud);

	go->SetWorldPosition(pos);

	return go;
}

std::shared_ptr<dae::GameObject> CreateLivesUI(const glm::vec3& pos, const std::string& texture)
{
	auto go = std::make_shared<dae::GameObject>();
	auto peterLives = go->AddComponent<LivesComponent>();
	peterLives->SetTexture(texture);
	peterLives->SetMaxLives(3);
	go->SetWorldPosition(pos);
	
	return go;
}

std::shared_ptr<dae::GameObject> CreatePepperCountUI(const glm::vec3& pos, const SDL_Color& pepperColor)
{
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	go->AddComponent<PepperUI>();
	auto pTextPepper = go->AddComponent<dae::TextComponent>();
	pTextPepper->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	pTextPepper->SetColor(pepperColor, false);
	go->SetWorldPosition(pos);

	auto child = go->AddChild();
	auto pRender = child->AddComponent<dae::RenderComponent>();
	pRender->SetTexture("BurgertimeSprites.png");
	pRender->UseSrc(true);
	pRender->SetSrc(216.f, 9.f, 24.f, 6.f);
	pRender->SetDst(0.f, 0.f, 50.f, 15.f);
	child->SetLocalPosition({ -20, -20, 0 });

	return go;
}

std::shared_ptr<dae::GameObject> CreateFPSCounter(const glm::vec3& pos, const SDL_Color& color)
{
	auto go = std::make_shared<dae::GameObject>();
	auto pTextComponent = go.get()->AddComponent<dae::TextComponent>();
	pTextComponent->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 13), false);
	pTextComponent->SetText("", false);
	pTextComponent->SetColor(color);
	go->AddComponent<dae::RenderComponent>();
	auto pFpsCounter = go->AddComponent<dae::FPSCounter>();
	pFpsCounter->UseSmoothing(true);
	go->SetWorldPosition(pos);
	
	return go;
}

std::shared_ptr<dae::GameObject> CreateScoreUI(const glm::vec3& pos, const SDL_Color& scoreColor, const SDL_Color& textColor)
{
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	go->AddComponent<ScoreComponent>();
	auto pTextScore = go->AddComponent<dae::TextComponent>();
	pTextScore->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	pTextScore->SetColor(scoreColor, false);
	go->SetWorldPosition(pos);

	auto child = go->AddChild();
	child->AddComponent<dae::RenderComponent>();
	pTextScore = child->AddComponent<dae::TextComponent>();
	pTextScore->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	pTextScore->SetColor(textColor, false);
	pTextScore->SetText("1UP");
	child->SetLocalPosition({ 20, -20, 0 });

	return go;
}

std::shared_ptr<dae::GameObject> CreateBackground(const std::string& texture)
{
	auto go = std::make_shared<dae::GameObject>();
	dae::RenderComponent* pBackgroundRender = go->AddComponent<dae::RenderComponent>();
	pBackgroundRender->SetTexture(texture);
	pBackgroundRender->SetDst(25.f, 100.f, 530.f, 530.f);
	return go;
}

std::shared_ptr<dae::GameObject> CreateLadder(const int ladderHeight, const glm::vec3& pos)
{
	const std::string ladderLabel = "Ladder";
	const int ladderWidth = 20;

	auto go = std::make_shared<dae::GameObject>();
	auto collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	auto l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition(pos);

	return go;
}

std::shared_ptr<dae::GameObject> CreatePlatform(const int platformWidth, const glm::vec3& pos)
{
	const std::string platformLabel = "Platform";
	const SDL_Color platformDebugColor = { 255, 0, 255, 255 };
	const int platformHeight = 8;

	auto go = std::make_shared<dae::GameObject>();
	auto collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	auto p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	auto debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition(pos);

	return go;
}

std::shared_ptr<dae::GameObject> CreateBurgerPart(dae::Observer* score, const glm::vec3& pos, const PartType type)
{
	const std::string burgerLabel = "Burger";

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	auto collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	auto b = go->AddComponent<BurgerPart>();
	b->SetType(type);
	b->AddObserver(score);
	go->SetWorldPosition(pos);

	return go;
}

std::shared_ptr<dae::GameObject> CreatePlate(const glm::vec3& pos)
{
	const std::string plateLabel = "Plate";
	const int width = 30;
	const int height = 80;

	auto go = std::make_shared<dae::GameObject>();
	auto collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(plateLabel);
	go->AddComponent<Plate>();
	auto debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(width, height);
	go->SetWorldPosition(pos);

	return go;
}

std::shared_ptr<dae::GameObject> CreateEnemy(dae::Observer* pGame, dae::Observer* score, dae::Observer* pSoundManager, Character* target, const glm::vec3& pos, const EnemyType type)
{
	int value = 0;

	switch (type)
	{
	case EnemyType::HotDog:
		value = 100;
		break;
	case EnemyType::Egg:
		value = 300;
		break;
	case EnemyType::Pickle:
		value = 200;
		break;
	}

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<HotdogController>()->SetTarget(target);
	go->AddComponent<dae::Collider>()->SetLabel("Enemy");
	go->AddComponent<dae::DebugRenderComponent>();
	go->AddComponent<dae::RenderComponent>()->SetTexture("BurgertimeSprites.png");
	auto e = go->AddComponent<Enemy>();
	e->SetType(type);
	e->SetValue(value);
	e->AddObserver(score);
	e->AddObserver(pSoundManager);
	e->AddObserver(pGame);
	go->SetWorldPosition(pos);
	
	return go;
}