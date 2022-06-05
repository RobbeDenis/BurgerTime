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

void LoadGame();

std::shared_ptr<dae::GameObject> CreatePlatform(const int platformWidth, const glm::vec3& pos);
std::shared_ptr<dae::GameObject> CreateLadder(const int ladderHeight, const glm::vec3& pos);
std::shared_ptr<dae::GameObject> CreateBurgerPart(dae::Observer* score, const glm::vec3& pos, const int type);
std::shared_ptr<dae::GameObject> CreatePlate(const glm::vec3& pos);
std::shared_ptr<dae::GameObject> CreateEnemy(dae::Observer* score, Character* target, const glm::vec3& pos, const int type);

SoundManager* g_pSoundManager = new SoundManager();

int main(int, char* []) 
{
	dae::RodEngine engine;

	engine.Initialize();

	dae::ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	engine.Run();

	delete g_pSoundManager;

	return 0;
}

void LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level");
	auto& input = dae::InputManager::GetInstance();

	scene.EnableDebugRender(false);

	// Adding sounds
	g_pSoundManager->SetVolume(0.1f);

	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::PlayerDied, "LoseLife.mp3");
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::BurgerWalk, "BurgerWalk.wav");
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::EnemyDied, "EnemyDied.wav");
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::PepperUsed, "Attack.wav");
	SoundSLocator::GetSoundSystem().RegisterSound(BTEvents::BurgerDropped, "Bounce.wav");

	// Adding GameObjects
	auto go = std::make_shared<dae::GameObject>();

	// Background
	dae::RenderComponent* pBackgroundRender = go->AddComponent<dae::RenderComponent>();
	pBackgroundRender->SetTexture("BurgerTimeBackground.png");
	pBackgroundRender->SetDst(25.f, 100.f, 530.f, 530.f);
	scene.Add(go);
	
	// FPS Counter
	go = std::make_shared<dae::GameObject>();
	dae::TextComponent* pTextComponent = go.get()->AddComponent<dae::TextComponent>();
	pTextComponent->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 13), false);
	pTextComponent->SetText("", false);
	pTextComponent->SetColor({ 40, 215, 67 });

	go->AddComponent<dae::RenderComponent>();
	dae::FPSCounter* pFpsCounter = go->AddComponent<dae::FPSCounter>();
	pFpsCounter->UseSmoothing(true);
	go->SetWorldPosition(7, 7);
	scene.Add(go);

	// Score component
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	ScoreComponent* peterScore = go->AddComponent<ScoreComponent>();
	dae::TextComponent* pTextScore = go->AddComponent<dae::TextComponent>();
	pTextScore->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	pTextScore->SetColor({ 255, 255, 255 }, false);
	go->SetWorldPosition(40, 23);
	scene.Add(go);

	auto child = go->AddChild();
	child->AddComponent<dae::RenderComponent>();
	pTextScore = child->AddComponent<dae::TextComponent>();
	pTextScore->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	pTextScore->SetColor({ 255, 0, 0 }, false);
	pTextScore->SetText("1UP");
	child->SetLocalPosition({ 20, -20, 0 });

	// Pepper count
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	PepperUI* pepperUI = go->AddComponent<PepperUI>();
	dae::TextComponent* pTextPepper = go->AddComponent<dae::TextComponent>();
	pTextPepper->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22), false);
	pTextPepper->SetColor({ 255, 255, 255 }, false);
	go->SetWorldPosition(550, 23);
	scene.Add(go);

	child = go->AddChild();
	auto pRender = child->AddComponent<dae::RenderComponent>();
	pRender->SetTexture("BurgertimeSprites.png");
	pRender->UseSrc(true);
	pRender->SetSrc(216.f, 9.f, 24.f, 6.f);
	pRender->SetDst(0.f, 0.f, 50.f, 15.f);
	child->SetLocalPosition({ -20, -20, 0 });

	// Lives
	go = std::make_shared<dae::GameObject>();
	LivesComponent* peterLives = go->AddComponent<LivesComponent>();
	peterLives->SetMaxLives(3);
	go->SetWorldPosition(5, 640);
	scene.Add(go);

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
	scene.Add(CreateBurgerPart(peterScore, { 67.f, 125.f, 0.f }, PartType::TopBun));
	scene.Add(CreateBurgerPart(peterScore, { 67.f, 211.f, 0.f }, PartType::Lettuce));
	scene.Add(CreateBurgerPart(peterScore, { 67.f, 295.f, 0.f }, PartType::Patty));
	scene.Add(CreateBurgerPart(peterScore, { 67.f, 507.f, 0.f }, PartType::BotBun));
	// Colum 2
	scene.Add(CreateBurgerPart(peterScore, { 190.f, 253.f, 0.f }, PartType::TopBun));
	scene.Add(CreateBurgerPart(peterScore, { 190.f, 337.f, 0.f }, PartType::Lettuce));
	scene.Add(CreateBurgerPart(peterScore, { 190.f, 423.f, 0.f }, PartType::Patty));
	scene.Add(CreateBurgerPart(peterScore, { 190.f, 507.f, 0.f }, PartType::BotBun));
	// Colum 3
	scene.Add(CreateBurgerPart(peterScore, { 312.f, 125.f, 0.f }, PartType::TopBun));
	scene.Add(CreateBurgerPart(peterScore, { 312.f, 211.f, 0.f }, PartType::Lettuce));
	scene.Add(CreateBurgerPart(peterScore, { 312.f, 337.f, 0.f }, PartType::Patty));
	scene.Add(CreateBurgerPart(peterScore, { 312.f, 507.f, 0.f }, PartType::BotBun));
	// Colum 4
	scene.Add(CreateBurgerPart(peterScore, { 435.f, 125.f, 0.f }, PartType::TopBun));
	scene.Add(CreateBurgerPart(peterScore, { 435.f, 211.f, 0.f }, PartType::Lettuce));
	scene.Add(CreateBurgerPart(peterScore, { 435.f, 295.f, 0.f }, PartType::Patty));
	scene.Add(CreateBurgerPart(peterScore, { 435.f, 380.f, 0.f }, PartType::BotBun));

	// Add plates
	scene.Add(CreatePlate({ 92.f, 548.f, 0.f }));
	scene.Add(CreatePlate({ 220.f, 548.f, 0.f }));
	scene.Add(CreatePlate({ 350.f, 548.f, 0.f }));
	scene.Add(CreatePlate({ 450.f, 548.f, 0.f }));

	// CREATING PETER PEPPER
	go = std::make_shared<dae::GameObject>();

	PeterPepper* pPeter = go->AddComponent<PeterPepper>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<dae::Collider>()->SetLabel("Player");
	go->AddComponent<dae::DebugRenderComponent>();

	dae::RenderComponent* pPeterPepperRender = go->AddComponent<dae::RenderComponent>();
	pPeterPepperRender->SetTexture("BurgertimeSprites.png");

	// Peter pepper
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Down }, std::make_unique<IMoveRight>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Down }, std::make_unique<IMoveLeft>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Down }, std::make_unique<IMoveUpLadder>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Down }, std::make_unique<IMoveDownLadder>(pPeter));

	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Released }, std::make_unique<IStopMove>(pPeter));

	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonA, dae::ButtonState::Pressed }, std::make_unique<IUseAbility>(pPeter));

	// Adding observors
	pPeter->AddObserver(peterScore);
	pPeter->AddObserver(peterLives);
	pPeter->AddObserver(pepperUI);
	pPeter->AddObserver(g_pSoundManager);

	go->SetWorldPosition(10, 500);

	scene.Add(go);

	// Adding pepper cloud
	go = std::make_shared<dae::GameObject>();
	PepperCloud* cloud = go->AddComponent<PepperCloud>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<dae::Collider>()->SetLabel("Pepper");
	go->AddComponent<dae::DebugRenderComponent>();
	go->AddComponent<dae::RenderComponent>()->SetTexture("BurgertimeSprites.png");
	scene.Add(go);
	pPeter->AddPepperCloud(cloud);

	// Adding hot dogs
	scene.Add(CreateEnemy(peterScore, pPeter, { 100.f, 120.f, 0.f }, EnemyType::HotDog));
	scene.Add(CreateEnemy(peterScore, pPeter, { 40.f, 120.f, 0.f }, EnemyType::HotDog));

	// Adding Egg
	scene.Add(CreateEnemy(peterScore, pPeter, { 500.f, 120.f, 0.f }, EnemyType::Egg));

	// Adding Pickle
	scene.Add(CreateEnemy(peterScore, pPeter, { 420.f, 330.f, 0.f }, EnemyType::Pickle));
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

std::shared_ptr<dae::GameObject> CreateBurgerPart(dae::Observer* score, const glm::vec3& pos, const int type)
{
	const std::string burgerLabel = "Burger";

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	auto collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	auto b = go->AddComponent<BurgerPart>();
	b->SetType(PartType(type));
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

std::shared_ptr<dae::GameObject> CreateEnemy(dae::Observer* score, Character* target, const glm::vec3& pos, const int type)
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
	e->SetType(EnemyType(type));
	e->SetValue(value);
	e->AddObserver(score);
	e->AddObserver(g_pSoundManager);
	go->SetWorldPosition(pos);
	
	return go;
}