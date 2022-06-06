#include "GameManager.h"
#include "BTEvents.h"
#include <SceneManager.h>
#include "UIPointer.h"

GameManager::GameManager()
	: dae::Observer()
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
	}
}

void GameManager::Confirmed(UIPointer* p)
{
	if (p)
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
	dae::SceneManager::GetInstance().Reset();
}

void GameManager::GameOver()
{
	ResetLevel();
	std::cout << "Game Over\n";
}