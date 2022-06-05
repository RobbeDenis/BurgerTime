#include "GameManager.h"
#include "BTEvents.h"
#include <SceneManager.h>

GameManager::GameManager()
	: dae::Observer()
{

}

GameManager::~GameManager()
{

}

void GameManager::Notify(int event)
{
	switch (event)
	{
	case BTEvents::PlayerDied:
		ResetLevel();
		break;
	}
}

void GameManager::ResetLevel()
{
	dae::SceneManager::GetInstance().Reset();
}