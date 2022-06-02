#include "BurgerPart.h"
#include <RenderComponent.h>

BurgerPart::BurgerPart(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Collider(nullptr)
	, m_Width(100)
	, m_Height(30)
	, m_Type(PartType::TopBun)
	, m_SrcH(8.f)
	, m_SrcW(31.f)
	, m_SrcX(112.f)
	, m_SrcY(48.f)
{

}

void BurgerPart::PostLoad()
{
	m_Collider = m_pGameObject->GetComponent<dae::Collider>();
	m_Collider->SetDimensions(m_Width, m_Height);

	dae::RenderComponent* renderComp = m_pGameObject->GetComponent<dae::RenderComponent>();
	renderComp->SetDst(m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y, float(m_Width), float(m_Height));
	renderComp->SetTexture("BurgertimeSprites.png");
	renderComp->UseSrc(true);
}

void BurgerPart::SetType(PartType type)
{
	m_Type = type;

	dae::RenderComponent* renderComp = m_pGameObject->GetComponent<dae::RenderComponent>();
	renderComp->SetSrc(m_SrcX, m_SrcY + (int(m_Type) * m_SrcH), m_SrcW, m_SrcH);
}