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
#include "Plate.h"
#include "ScoreComponent.h"
#include "LivesComponent.h"
#include "Enemy.h"
#include "HotdogController.h"
#include "PickleController.h"
#include "PepperCloud.h"
#include "PepperUI.h"

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

	scene.EnableDebugRender(false);

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
	go->SetWorldPosition({ 392.f, 387.f, 0.f });
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
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 67.f, 125.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Lettuce);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 67.f, 211.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Patty);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 67.f, 295.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::BotBun);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 67.f, 507.f, 0.f });
	scene.Add(go);

	// Colum 2
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::TopBun);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 190.f, 253.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Lettuce);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 190.f, 337.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Patty);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 190.f, 423.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::BotBun);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 190.f, 507.f, 0.f });
	scene.Add(go);

	// Colum 3
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::TopBun);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 312.f, 125.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Lettuce);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 312.f, 211.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Patty);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 312.f, 337.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::BotBun);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 312.f, 507.f, 0.f });
	scene.Add(go);

	// Colum 4
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::TopBun);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 435.f, 125.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Lettuce);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 435.f, 211.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::Patty);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 435.f, 295.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(burgerLabel);
	b = go->AddComponent<BurgerPart>();
	b->SetType(PartType::BotBun);
	b->AddObserver(peterScore);
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(79, 15);
	go->SetWorldPosition({ 435.f, 380.f, 0.f });
	scene.Add(go);

	// Add plates
	const std::string plateLabel = "Plate";
	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(plateLabel);
	go->AddComponent<Plate>();
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(30, 80);
	go->SetWorldPosition({ 92.f, 548.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(plateLabel);
	go->AddComponent<Plate>();
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(30, 80);
	go->SetWorldPosition({ 220.f, 548.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(plateLabel);
	go->AddComponent<Plate>();
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(30, 80);
	go->SetWorldPosition({ 350.f, 548.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	collider = go->AddComponent<dae::Collider>();
	collider->SetLabel(plateLabel);
	go->AddComponent<Plate>();
	debugRender = go->AddComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(30, 80);
	go->SetWorldPosition({ 450.f, 548.f, 0.f });
	scene.Add(go);

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

	go->SetWorldPosition(10, 500);

	scene.Add(go);

	// Adding hot dogs
	const int hotdogValue = 100;
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<HotdogController>()->SetTarget(pPeter);
	go->AddComponent<dae::Collider>()->SetLabel("Enemy");
	go->AddComponent<dae::DebugRenderComponent>();
	go->AddComponent<dae::RenderComponent>()->SetTexture("BurgertimeSprites.png");
	Enemy* e = go->AddComponent<Enemy>();
	e->SetType(EnemyType::HotDog);
	e->SetValue(hotdogValue);
	e->AddObserver(peterScore);
	go->SetWorldPosition({ 40.f, 120.f, 0.f });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<HotdogController>()->SetTarget(pPeter);
	go->AddComponent<dae::Collider>()->SetLabel("Enemy");
	go->AddComponent<dae::DebugRenderComponent>();
	go->AddComponent<dae::RenderComponent>()->SetTexture("BurgertimeSprites.png");
	e = go->AddComponent<Enemy>();
	e->SetType(EnemyType::HotDog);
	e->SetValue(hotdogValue);
	e->AddObserver(peterScore);
	go->SetWorldPosition({ 50.f, 120.f, 0.f });
	scene.Add(go);

	// Adding Egg
	const int eggValue = 300;
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<HotdogController>()->SetTarget(pPeter);
	go->AddComponent<dae::Collider>()->SetLabel("Enemy");
	go->AddComponent<dae::DebugRenderComponent>();
	go->AddComponent<dae::RenderComponent>()->SetTexture("BurgertimeSprites.png");
	e = go->AddComponent<Enemy>();
	e->SetType(EnemyType::Egg);
	e->SetValue(eggValue);
	e->AddObserver(peterScore);
	go->SetWorldPosition({ 500.f, 120.f, 0.f });
	scene.Add(go);


	// Adding Pickle
	const int pickleValue = 200;
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Animator>();
	go->AddComponent<PickleController>()->SetTarget(pPeter);
	go->AddComponent<dae::Collider>()->SetLabel("Enemy");
	go->AddComponent<dae::DebugRenderComponent>();
	go->AddComponent<dae::RenderComponent>()->SetTexture("BurgertimeSprites.png");
	e = go->AddComponent<Enemy>();
	e->SetType(EnemyType::Pickle);
	e->SetValue(pickleValue);
	e->AddObserver(peterScore);
	go->SetWorldPosition({ 420.f, 330.f, 0.f });
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
}