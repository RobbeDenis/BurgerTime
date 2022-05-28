#include "RodEnginePCH.h"
#include "LivesComponent.h"
#include "PeterPepper.h"
#include "TextComponent.h"
#include "ResourceManager.h"

dae::LivesComponent::LivesComponent(GameObject* gameObject)
	: BaseComponent(gameObject)
{

}

void dae::LivesComponent::PostLoad()
{
	m_pTextLives = m_pGameObject->GetComponent<TextComponent>();
}

void dae::LivesComponent::Notify(BaseComponent* pComponent, Event event)
{
	PeterPepper* peter = dynamic_cast<PeterPepper*>(pComponent);
	if (peter == nullptr)
		return;

	switch (event)
	{
	case Event::PlayerDied:
		PlayerDied(peter);
		break;
	case Event::PlayerReset:
		PlayerDied(peter);
	}
}

void dae::LivesComponent::PlayerDied(PeterPepper* peter)
{
	m_pTextLives->SetText("Lives: " + std::to_string(peter->GetLives()));
}

void dae::LivesComponent::SetColor(const SDL_Color& color)
{
	m_pTextLives->SetColor(color);
}
