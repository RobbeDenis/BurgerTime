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

#include "BurgerTimeCommands.h"
#include "Platform.h"
#include "Ladder.h"

using namespace dae;

void LoadGame();

int main(int, char* []) 
{
	dae::RodEngine engine;

	engine.Initialize();

	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	engine.Run();
	return 0;
}

void LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level");
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
	go->AddComponent<Collider>();
	go->AddComponent<DebugRenderComponent>();

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

	go->SetWorldPosition(150, 50);

	scene.Add(go);

	// Adding Ladders
	const std::string ladderLabel = "Ladder";
	const int ladderWidth = 20;
	int ladderHeight = 90;

	// First row
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	Collider* collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 36.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 385;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 158.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 130;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 219.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 385;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 280.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 385;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 402.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 173;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 525.f, 135.f, 0.f });
	scene.Add(go);

	// Second row
	ladderHeight = 215;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 96.f, 221.f, 0.f });
	scene.Add(go);

	ladderHeight = 130;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 341.f, 221.f, 0.f });
	scene.Add(go);

	// Third row
	ladderHeight = 213;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 36.f, 307.f, 0.f });
	scene.Add(go);

	ladderHeight = 213;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 463.f, 307.f, 0.f });
	scene.Add(go);

	// Forth row
	ladderHeight = 128;
	go = std::make_shared<GameObject>();
	go->AddComponent<Ladder>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	collider->SetLabel(ladderLabel);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 524.f, 390.f, 0.f });
	scene.Add(go);

	// Adding platforms
	const std::string platformLabel = "Platform";
	const SDL_Color platformDebugColor = { 255, 0, 255, 255 };
	const int platformHeight = 6;
	int platformWidth = 530;

	// Row 1
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	DebugRenderComponent* debugRender = go->AddComponent<DebugRenderComponent>(); 
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 25.f, 135.f, 0.f });
	scene.Add(go);

	// Row 2
	platformWidth = 163;
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	debugRender = go->AddComponent<DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 25.f, 220.f, 0.f });
	scene.Add(go);

	platformWidth = 285;
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	debugRender = go->AddComponent<DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 270.f, 220.f, 0.f });
	scene.Add(go);

	// Row 3
	platformWidth = 164;
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	debugRender = go->AddComponent<DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 147.f, 262.f, 0.f });
	scene.Add(go);

	// Row 4
	platformWidth = 163;
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	debugRender = go->AddComponent<DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 25.f, 304.f, 0.f });
	scene.Add(go);

	platformWidth = 163;
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	debugRender = go->AddComponent<DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 392.f, 304.f, 0.f });
	scene.Add(go);

	// Row 5
	platformWidth = 285;
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	debugRender = go->AddComponent<DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 148.f, 346.f, 0.f });
	scene.Add(go);

	// Row 6
	platformWidth = 165;
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	debugRender = go->AddComponent<DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 391.f, 389.f, 0.f });
	scene.Add(go);

	// Row 7
	platformWidth = 410;
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	debugRender = go->AddComponent<DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 24.f, 432.f, 0.f });
	scene.Add(go);

	// Row 8
	platformWidth = 530;
	go = std::make_shared<GameObject>();
	go->AddComponent<Platform>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(platformWidth, platformHeight);
	collider->SetLabel(platformLabel);
	debugRender = go->AddComponent<DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 25.f, 516.f, 0.f });
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
}