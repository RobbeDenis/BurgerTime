#include "BurgerPart.h"
#include <RenderComponent.h>
#include <ETime.h>

BurgerPart::BurgerPart(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Collider(nullptr)
	, m_Width(83)
	, m_Height(15)
	, m_Type(PartType::TopBun)
	, m_SrcH(8.f)
	, m_SrcW(31.f)
	, m_SrcX(112.f)
	, m_SrcY(48.f)
	, m_FallSpeed(80.f)
	, m_IsFalling(false)
{

}

void BurgerPart::PostLoad()
{
	m_Collider = m_pGameObject->GetComponent<dae::Collider>();
	m_Collider->SetDimensions(m_Width, m_Height);

	dae::RenderComponent* renderComp = m_pGameObject->GetComponent<dae::RenderComponent>();
	renderComp->SetDst(0.f, 0.f, float(m_Width), float(m_Height));
	renderComp->SetTexture("BurgertimeSprites.png");
	renderComp->UseSrc(true);
}

void BurgerPart::FixedUpdate()
{
	HandleOverlaps();

	if (m_IsFalling)
	{
		glm::vec3 newPos = m_pGameObject->GetWorldPosition();
		newPos.y += m_FallSpeed * dae::ETime::GetInstance().GetDeltaTime();
		m_pGameObject->SetWorldPosition(newPos);
	}
}

void BurgerPart::Update()
{

}

void BurgerPart::HandleOverlaps()
{
	for (dae::Collider* c : m_Collider->GetColliders())
	{
		if (c == m_Collider)
			continue;

		if (c->GetLabel() == "Player")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
				Fall();
		}
	}
}

void BurgerPart::Fall()
{
	m_IsFalling = true;
}

void BurgerPart::SetType(PartType type)
{
	m_Type = type;

	dae::RenderComponent* renderComp = m_pGameObject->GetComponent<dae::RenderComponent>();
	renderComp->SetSrc(m_SrcX, m_SrcY + (int(m_Type) * m_SrcH), m_SrcW, m_SrcH);
}