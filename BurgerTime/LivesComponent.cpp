#include "LivesComponent.h"
#include "PeterPepper.h"
#include "ResourceManager.h"
#include "BTEvents.h"

LivesComponent::LivesComponent(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Offset(28)
	, m_Height(22)
	, m_Width(22)
	, m_Texture("BurgertimeSprites.png")
{

}

void LivesComponent::PostLoad()
{
	for (int i = 0; i < m_RenderComponents.size(); ++i)
	{
		m_RenderComponents[i]->SetDst(0.f, -float(m_Offset * (i + 1)), float(m_Width), float(m_Height));
	}
}

void LivesComponent::SetMaxLives(const int lives)
{
	for (int i = 0; i < lives; ++i)
	{
		dae::RenderComponent* c = m_pGameObject->AddComponent<dae::RenderComponent>();
		c->SetTexture(m_Texture);
		c->UseSrc(true);
		c->SetSrc(201.f, 0.f, 7.f, 8.f);

		m_RenderComponents.push_back(c);

	}
}

void LivesComponent::Notify(BaseComponent* pComponent, int event)
{
	PeterPepper* peter = dynamic_cast<PeterPepper*>(pComponent);
	if (peter == nullptr)
		return;

	switch (event)
	{
	case BTEvents::PlayerDied:
	case BTEvents::PlayerReset:
		PlayerDied(peter);
		break;
	}
}

void LivesComponent::PlayerDied(PeterPepper* peter)
{
	for (int i = 0; i < m_RenderComponents.size(); ++i)
	{
		if (i < peter->GetLives())
		{
			m_RenderComponents[i]->SetDst(0.f, -float(m_Offset * (i + 1)), float(m_Width), float(m_Height));
		}
		else
		{
			m_RenderComponents[i]->SetDst(0.f, -float(m_Offset * (i + 1)), 0.f, 0.f);
		}
	}
}

