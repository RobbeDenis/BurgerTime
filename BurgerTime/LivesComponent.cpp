#include "LivesComponent.h"
#include "PeterPepper.h"
#include "ResourceManager.h"
#include "BTEvents.h"

LivesComponent::LivesComponent(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
{

}

void LivesComponent::PostLoad()
{
	m_pTextLives = m_pGameObject->GetComponent<dae::TextComponent>();
}

void LivesComponent::Notify(BaseComponent* pComponent, int event)
{
	PeterPepper* peter = dynamic_cast<PeterPepper*>(pComponent);
	if (peter == nullptr)
		return;

	switch (event)
	{
	case BTEvents::PlayerDied:
		PlayerDied(peter);
		break;
	case BTEvents::PlayerReset:
		PlayerDied(peter);
	}
}

void LivesComponent::PlayerDied(PeterPepper* peter)
{
	m_pTextLives->SetText(std::to_string(peter->GetLives()));
}

void LivesComponent::SetColor(const SDL_Color& color)
{
	m_pTextLives->SetColor(color);
}
