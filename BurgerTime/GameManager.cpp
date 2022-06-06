#include "GameManager.h"
#include "BTEvents.h"
#include <SceneManager.h>
#include "UIPointer.h"
#include <InputManager.h>
#include "RespawnManager.h"

GameManager::GameManager()
	: dae::Observer()
	, m_IsGameOver(false)
	, m_MaxPlatesFilled(4)
	, m_PlatesFilled(0)
{

}

GameManager::~GameManager()
{

}

void GameManager::Notify(dae::BaseComponent* c, int event)
{
	switch (event)
	{
	case BTEvents::UIConfirmed:
		Confirmed(static_cast<UIPointer*>(c));
		break;
	}
	Notify(event);
}

void GameManager::Notify(int event)
{
	switch (event)
	{
	case BTEvents::PlayerDied:
		ResetLevel();
		break;
	case BTEvents::GameOver:
		GameOver();
		break;
	case BTEvents::PlateFilled:
		PlateFilled();
		break;
	}
}

void GameManager::PlateFilled()
{
	++m_PlatesFilled;
	if (m_PlatesFilled >= m_MaxPlatesFilled)
	{
		GameWon();
		m_PlatesFilled = 0;
	}
}

void GameManager::Confirmed(UIPointer* p)
{
	if (m_IsGameOver)
	{
		m_IsGameOver = false;
		ResetWholeScene();
		dae::SceneManager::GetInstance().SetScene(m_StartMenu);
	}
	else if (p)
	{
		int index = p->GetIndex();
		switch (index)
		{
		case 0:
		{
			dae::SceneManager::GetInstance().SetScene(m_SinglePlayer);
			break;
		}
		case 1:
		{
			dae::SceneManager::GetInstance().SetScene(m_Coop);
			break;
		}
		case 2:
		{
			dae::SceneManager::GetInstance().SetScene(m_Versus);
			break;
		}
		}
	}
}

void GameManager::ResetLevel()
{
	RespawnManager::GetInstance().Respawn();
}

void GameManager::GameOver()
{
	ResetLevel();
	std::cout << "Game Over\n";
	m_IsGameOver = true;

	ResetWholeScene();
	dae::SceneManager::GetInstance().SetScene(m_GameOver);
}

void GameManager::ResetWholeScene()
{
	dae::InputManager::GetInstance().Reset();
	dae::SceneManager::GetInstance().Reset();
}

void GameManager::GameWon()
{
	ResetLevel();
	std::cout << "Game Won\n";
	m_IsGameOver = true;
	ResetWholeScene();
	dae::SceneManager::GetInstance().SetScene(m_GameWon);
}