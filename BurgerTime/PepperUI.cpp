#include "PepperUI.h"
#include "PeterPepper.h"
#include "ResourceManager.h"
#include "BTEvents.h"

PepperUI::PepperUI(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
{

}

void PepperUI::PostLoad()
{
	m_pTextLives = m_pGameObject->GetComponent<dae::TextComponent>();
}

void PepperUI::Notify(BaseComponent* pComponent, int event)
{
	PeterPepper* peter = dynamic_cast<PeterPepper*>(pComponent);
	if (peter == nullptr)
		return;

	switch (event)
	{
	case BTEvents::PepperUsed:
		PepperUsed(peter);
		break;
	case BTEvents::PlayerReset:
		PepperUsed(peter);
		break;
	}
}

void PepperUI::PepperUsed(PeterPepper* peter)
{
	m_pTextLives->SetText(std::to_string(peter->GetPepperCount()));
}

void PepperUI::SetColor(const SDL_Color& color)
{
	m_pTextLives->SetColor(color);
}
