#include "RodEnginePCH.h"
#include "ScoreComponent.h"
#include "ResourceManager.h"
#include "BTEvents.h"
#include "Enemy.h"
#include "BurgerPart.h"

ScoreComponent::ScoreComponent(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
{

}

void ScoreComponent::PostLoad()
{
	m_pTextPoints = m_pGameObject->GetComponent<dae::TextComponent>();
}

void ScoreComponent::Notify(BaseComponent* c, int event)
{
	switch (event)
	{
	case BTEvents::EnemyDied:
		EnemyDied(c);
		break;
	case BTEvents::EnemiesDiedOnTop:
		EnemiesOnTop(c);
		break;
	}

	Notify(event);
}

void ScoreComponent::Notify(int event)
{
	switch (event)
	{
	case BTEvents::BurgerDropped:
		BurgerDropped();
		break;
	case BTEvents::PlayerReset:
		ResetScore();
	}
}

void ScoreComponent::EnemiesOnTop(BaseComponent* burgerPart)
{
	BurgerPart* b = static_cast<BurgerPart*>(burgerPart);
	m_Score += b->GetEnemiesOnTop() * m_BaseEnemyValue;

	m_pTextPoints->SetText(std::to_string(m_Score));
}

void ScoreComponent::EnemyDied(BaseComponent* enemy)
{
	Enemy* e = static_cast<Enemy*>(enemy);
	m_Score += e->GetValue();

	m_pTextPoints->SetText(std::to_string(m_Score));
}

void ScoreComponent::BurgerDropped()
{
	m_Score += m_BurgerValue;
	m_pTextPoints->SetText(std::to_string(m_Score));
}

void ScoreComponent::ResetScore()
{
	m_Score = 0;
	m_pTextPoints->SetText(std::to_string(m_Score));
}

void ScoreComponent::SetColor(const SDL_Color& color)
{
	m_pTextPoints->SetColor(color);
}
