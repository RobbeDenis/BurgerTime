#include "RodEnginePCH.h"
#include "ScoreComponent.h"
#include "ResourceManager.h"

ScoreComponent::ScoreComponent(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_KillValue{ m_BaseKillValue }
{

}

void ScoreComponent::PostLoad()
{
	m_pTextPoints = m_pGameObject->GetComponent<dae::TextComponent>();
}

void ScoreComponent::Notify(dae::Event event)
{
	switch (event)
	{
	case dae::Event::EnemyDied:
		EnemyDied();
		break;
	case dae::Event::BurgerDropped:
		BurgerDropped();
		break;
	case dae::Event::PlayerReset:
		ResetScore();
	}
}

void ScoreComponent::EnemyDied()
{
	m_Score += m_KillValue;
	m_KillValue *= 2;

	m_pTextPoints->SetText(std::to_string(m_Score));
	CheckIfGameWon();
}

void ScoreComponent::BurgerDropped()
{
	m_Score += 50;
	m_pTextPoints->SetText(std::to_string(m_Score));
	CheckIfGameWon();
}

void ScoreComponent::ResetScore()
{
	m_Score = 0;
	m_KillValue = m_BaseKillValue;
	m_pTextPoints->SetText(std::to_string(m_Score));
}

void ScoreComponent::SetColor(const SDL_Color& color)
{
	m_pTextPoints->SetColor(color);
}

void ScoreComponent::CheckIfGameWon()
{
	
}
