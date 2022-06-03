#include "BurgerPart.h"
#include <RenderComponent.h>
#include <ETime.h>
#include "Plate.h"
#include "BTEvents.h"

BurgerPart::BurgerPart(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Collider(nullptr)
	, m_Width(79)
	, m_Height(15)
	, m_Type(PartType::TopBun)
	, m_SrcH(8.f)
	, m_SrcW(31.f)
	, m_SrcX(112.f)
	, m_SrcY(48.f)
	, m_FallSpeed(80.f)
	, m_IsFalling(false)
	, m_OverlapPlatform(false)
	, m_BeginOverlapPlatform(false)
	, m_PrevOverlapPlatform(false)
	, m_HitPart(false)
	, m_Stacking(false)
	, m_TotalSegments(7)
	, m_Segments{}
{
	m_pSubject = std::make_shared<dae::Subject>();

	for (int i = 0; i < m_TotalSegments; i++)
	{
		m_Segments.push_back(false);
	}
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

void BurgerPart::HandleOverlaps()
{
	m_OverlapPlatform = false;

	for (dae::Collider* c : m_Collider->GetColliders())
	{
		if (c == m_Collider)
			continue;

		if (c->GetLabel() == "Player")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				int otherMid = int(c->GetGameObject()->GetWorldPosition().x) + (c->GetRect().w / 2);
				int left = int(m_pGameObject->GetWorldPosition().x);
				int segmentLength = m_Width / m_TotalSegments;

				for (int i = 0; i < m_TotalSegments; i++)
				{
					if (otherMid >= left + (segmentLength * i) &&
						otherMid <= left + (segmentLength * i + 1))
						m_Segments[i] = true;
				}

				bool canFall = true;
				for (bool b : m_Segments)
					canFall &= b;

				if (canFall)
					Fall();
			}
		}
		if (m_IsFalling && !m_HitPart && c->GetLabel() == "Burger")
		{				
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				BurgerPart* b = c->GetGameObject()->GetComponent<BurgerPart>();

				if (m_Stacking)
				{
					m_pSubject->Notify(BTEvents::BurgerDropped);
					m_IsFalling = false;
				}
				// Only let the part fall if this comes from above
				else if (m_pGameObject->GetWorldPosition().y < c->GetGameObject()->GetWorldPosition().y)
				{
					b->Fall();
					m_HitPart = true;
				}
			}
		}
		if (c->GetLabel() == "Platform")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				m_OverlapPlatform = true;
				m_BeginOverlapPlatform = !m_PrevOverlapPlatform;

				if (m_BeginOverlapPlatform)
				{
					m_IsFalling = false;
					m_HitPart = false;
				}
			}
		}
		if (m_IsFalling && m_Stacking && c->GetLabel() == "Plate")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				Plate* p = c->GetGameObject()->GetComponent<Plate>();

				glm::vec3 newPos = m_pGameObject->GetWorldPosition();
				if (p->CalculateClampedPos(newPos, m_Height))
				{
					m_pGameObject->SetWorldPosition(newPos);
					m_IsFalling = false;
					m_pSubject->Notify(BTEvents::BurgerDropped);
				}
			}
		}
	}

	m_PrevOverlapPlatform = m_OverlapPlatform;
}

void BurgerPart::Fall()
{
	m_IsFalling = true;
	m_HitPart = false;
	ResetSegments();
}

void BurgerPart::ResetSegments()
{
	for (int i = 0; i < m_TotalSegments; i++)
		m_Segments[i] = false;
}

void BurgerPart::SetType(PartType type)
{
	m_Type = type;

	dae::RenderComponent* renderComp = m_pGameObject->GetComponent<dae::RenderComponent>();
	renderComp->SetSrc(m_SrcX, m_SrcY + (int(m_Type) * m_SrcH), m_SrcW, m_SrcH);
}

void BurgerPart::AddObserver(dae::Observer* observer)
{
	m_pSubject->AddObserver(observer);
}