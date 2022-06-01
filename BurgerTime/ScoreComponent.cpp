#include "RodEnginePCH.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"

dae::ScoreComponent::ScoreComponent(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_KillValue{ m_BaseKillValue }
{

}

void dae::ScoreComponent::PostLoad()
{
	m_pTextPoints = m_pGameObject->GetComponent<TextComponent>();
}

void dae::ScoreComponent::Notify(Event event)
{
	switch (event)
	{
	case Event::EnemyDied:
		EnemyDied();
		break;
	case Event::BurgerDropped:
		BurgerDropped();
		break;
	case Event::PlayerReset:
		ResetScore();
	}
}

void dae::ScoreComponent::EnemyDied()
{
	m_Score += m_KillValue;
	m_KillValue *= 2;

	m_pTextPoints->SetText("Score: " + std::to_string(m_Score));
	CheckIfGameWon();
}

void dae::ScoreComponent::BurgerDropped()
{
	m_Score += 50;
	m_pTextPoints->SetText("Score: " + std::to_string(m_Score));
	CheckIfGameWon();
}

void dae::ScoreComponent::ResetScore()
{
	m_Score = 0;
	m_KillValue = m_BaseKillValue;
	m_pTextPoints->SetText("Score: " + std::to_string(m_Score));
}

void dae::ScoreComponent::SetColor(const SDL_Color& color)
{
	m_pTextPoints->SetColor(color);
}

void dae::ScoreComponent::CheckIfGameWon()
{
	if (m_Score >= m_ScoreToWin)
	{
		
	}
}
