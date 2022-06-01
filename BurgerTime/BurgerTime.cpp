// BurgerTime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include <memory>
#include <vector>
#include <string>

#pragma warning(push, 0)
#pragma warning(disable:26495)
#pragma warning(disable:26812)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

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

	go->SetWorldPosition(150, 150);

	scene.Add(go);

	// Adding Ladders
	int ladderWidth = 20;
	int ladderHeight = 90;

	// First row
	go = std::make_shared<GameObject>();
	Collider* collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 36.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 385;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 158.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 130;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 219.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 385;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 280.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 385;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 402.f, 135.f, 0.f });
	scene.Add(go);

	ladderHeight = 173;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 525.f, 135.f, 0.f });
	scene.Add(go);

	// Second row
	ladderHeight = 215;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 96.f, 221.f, 0.f });
	scene.Add(go);

	ladderHeight = 130;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 341.f, 221.f, 0.f });
	scene.Add(go);

	// Third row
	ladderHeight = 213;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 36.f, 307.f, 0.f });
	scene.Add(go);

	ladderHeight = 213;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 463.f, 307.f, 0.f });
	scene.Add(go);

	// Forth row
	ladderHeight = 128;
	go = std::make_shared<GameObject>();
	collider = go->AddComponent<Collider>();
	collider->SetDimensions(ladderWidth, ladderHeight);
	go->AddComponent<DebugRenderComponent>()->SetDimensions(ladderWidth, ladderHeight);
	go->SetWorldPosition({ 524.f, 390.f, 0.f });
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