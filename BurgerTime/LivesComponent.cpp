#include "LivesComponent.h"
#include "PeterPepper.h"
#include "ResourceManager.h"

LivesComponent::LivesComponent(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
{

}

void LivesComponent::PostLoad()
{
	m_pTextLives = m_pGameObject->GetComponent<dae::TextComponent>();
}

void LivesComponent::Notify(BaseComponent* pComponent, dae::Event event)
{
	PeterPepper* peter = dynamic_cast<PeterPepper*>(pComponent);
	if (peter == nullptr)
		return;

	switch (event)
	{
	case dae::Event::PlayerDied:
		PlayerDied(peter);
		break;
	case dae::Event::PlayerReset:
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
