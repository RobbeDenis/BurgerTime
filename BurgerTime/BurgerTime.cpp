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

#include "PeterPepper.h"
#include "BurgerTimeCommands.h"
#include "Platform.h"
#include "Ladder.h"
#include "BurgerPart.h"

void LoadGame();

int main(int, char* []) 
{
	dae::RodEngine engine;

	engine.Initialize();

	dae::ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	engine.Run();
	return 0;
}

void LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level");
	auto& input = dae::InputManager::GetInstance();
	auto go = std::make_shared<dae::GameObject>();

	scene.EnableDebugRender(true);

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

	// Adding Ladders
	const std::string ladderLabel = "Ladder";
	const int ladderWidth = 20;
	int ladderHeight = 90;

	// First row
	go = std::make_shared<dae::GameObject>();
	dae::Collider* collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	Ladder* l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 36.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 385;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 158.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 130;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 219.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 385;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 280.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 385;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 402.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 173;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 525.f, 135.f, 0.f });
	scene.Add(go);

	// Second row
	ladderHeight = 215;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 96.f, 221.f, 0.f });
	scene.Add(go);

	ladderHeight = 130;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 341.f, 221.f, 0.f });
	scene.Add(go);

	// Third row
	ladderHeight = 213;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 36.f, 306.f, 0.f });
	scene.Add(go);

	ladderHeight = 213;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 463.f, 306.f, 0.f });
	scene.Add(go);

	// Forth row
	ladderHeight = 128;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(ladderLabel);
	l = go->AddComponent<Ladder>();
	l->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<dae::DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 524.f, 390.f, 0.f });
	scene.Add(go);

	// Adding platforms
	const std::string platformLabel = "Platform";
	const SDL_Color platformDebugColor = { 255, 0, 255, 255 };
	const int platformHeight = 8;
	int platformWidth = 530;

	// Row 1
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	Platform * p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	dae::DebugRenderComponent* debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 25.f, 133.f, 0.f });
	scene.Add(go);

	// Row 2
	platformWidth = 163;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 25.f, 218.f, 0.f });
	scene.Add(go);

	platformWidth = 285;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 270.f, 218.f, 0.f });
	scene.Add(go);

	// Row 3
	platformWidth = 164;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 147.f, 260.f, 0.f });
	scene.Add(go);

	// Row 4
	platformWidth = 163;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 25.f, 302.f, 0.f });
	scene.Add(go);

	platformWidth = 163;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 392.f, 302.f, 0.f });
	scene.Add(go);

	// Row 5
	platformWidth = 285;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 148.f, 344.f, 0.f });
	scene.Add(go);

	// Row 6
	platformWidth = 165;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 391.f, 387.f, 0.f });
	scene.Add(go);

	// Row 7
	platformWidth = 410;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 24.f, 430.f, 0.f });
	scene.Add(go);

	// Row 8
	platformWidth = 530;
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(platformLabel);
	p = go->AddComponent<Platform>();
	p->SetDimensions(platformWidth, platformHeight);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(platformWidth, platformHeight);
	debugRender->SetColor(platformDebugColor);
	go->SetWorldPosition({ 25.f, 514.f, 0.f });
	scene.Add(go);

	// Adding Burger parts
	const std::string burgerLabel = "Burger";

	// Colum 1
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	BurgerPart* b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::TopBun);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 65.f, 125.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Lettuce);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 65.f, 211.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Patty);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 65.f, 295.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::BotBun);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 65.f, 507.f, 0.f });
	scene.Add(go);

	// Colum 2
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::TopBun);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 188.f, 253.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Lettuce);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 188.f, 337.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Patty);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 188.f, 423.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::BotBun);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 188.f, 507.f, 0.f });
	scene.Add(go);

	// Colum 3
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::TopBun);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 309.f, 125.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Lettuce);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 309.f, 211.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Patty);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 309.f, 337.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::BotBun);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 309.f, 507.f, 0.f });
	scene.Add(go);

	// Colum 4
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::TopBun);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 431.f, 125.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Lettuce);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 431.f, 211.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Patty);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 431.f, 295.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::BotBun);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(83, 15);
	go->SetWorldPosition({ 431.f, 380.f, 0.f });
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

	// CREATING PETER PEPPER
	go = std::make_shared<dae::GameObject>();

	PeterPepper* pPeter = go->AddComponent<PeterPepper>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<dae::Collider>();
	go->AddComponent<dae::DebugRenderComponent>();

	dae::RenderComponent* pPeterPepperRender = go->AddComponent<dae::RenderComponent>();
	pPeterPepperRender->SetTexture("BurgertimeSprites.png");

	// Peter pepper
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Down }, std::make_unique<PeterMoveRight>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Down }, std::make_unique<PeterMoveLeft>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Down }, std::make_unique<PeterMoveUpLadder>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Down }, std::make_unique<PeterMoveDownLadder>(pPeter));

	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonRight, dae::ButtonState::Released }, std::make_unique<PeterStopMove>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonLeft, dae::ButtonState::Released }, std::make_unique<PeterStopMove>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonUp, dae::ButtonState::Released }, std::make_unique<PeterStopMove>(pPeter));
	input.AddControllerCommand({ dae::XBox360Controller::ControllerButton::ButtonDown, dae::ButtonState::Released }, std::make_unique<PeterStopMove>(pPeter));

	go->SetWorldPosition(10, 500);

	scene.Add(go);
}