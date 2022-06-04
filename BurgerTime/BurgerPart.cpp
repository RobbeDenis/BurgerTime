#include "BurgerPart.h"
#include <RenderComponent.h>
#include <ETime.h>
#include "Plate.h"
#include "BTEvents.h"
#include "Enemy.h"
#include "SoundSystem.h"

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
	, m_FallSpeed(200.f)
	, m_IsFalling(false)
	, m_OverlapPlatform(false)
	, m_BeginOverlapPlatform(false)
	, m_PrevOverlapPlatform(false)
	, m_HitPart(false)
	, m_Stacking(false)
	, m_TotalSegments(5)
	, m_Segments{}
	, m_FallCounter{}
	, m_BounceHeight{6}
	, m_PlayerFall(false)
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
	else if(m_FallCounter > 0)
	{
		--m_FallCounter;
		Fall();
	}
}

void BurgerPart::HandleOverlaps()
{
	m_OverlapPlatform = false;

	for (dae::Collider* c : m_Collider->GetColliders())
	{
		if (c == m_Collider)
			continue;

		if (!m_IsFalling && c->GetLabel() == "Player")
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
					{
						if (m_Segments[i] == false)
						{
							m_Segments[i] = true;
							SoundSLocator::GetSoundSystem().Play(BTEvents::BurgerWalk, 0.1f);
						}
					}
				}

				bool canFall = true;
				for (bool b : m_Segments)
					canFall &= b;

				if (canFall)
				{
					m_PlayerFall = false;
					Fall();
				}
			}
		}
		if (m_IsFalling && !m_HitPart && c->GetLabel() == "Burger")
		{				
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				if(m_IsFalling)
					SoundSLocator::GetSoundSystem().Play(BTEvents::BurgerDropped, 0.1f);

				BurgerPart* b = c->GetGameObject()->GetComponent<BurgerPart>();

				if (m_Stacking)
				{
					m_pSubject->Notify(BTEvents::BurgerDropped);
					m_IsFalling = false;
				}
				// Only let the part fall if this comes from above
				else if (m_pGameObject->GetWorldPosition().y < c->GetGameObject()->GetWorldPosition().y)
				{
					glm::vec3 newPos = c->GetGameObject()->GetWorldPosition();
					newPos.y += m_BounceHeight;
					c->GetGameObject()->SetWorldPosition(newPos);

					if (m_FallCounter > 0)
					{
						b->Fall(true);
						m_HitPart = true;
					}
					else
					{
						b->Fall();
						m_HitPart = true;
					}
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
					if (m_IsFalling)
						SoundSLocator::GetSoundSystem().Play(BTEvents::BurgerDropped, 0.1f);

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
				}
			}
		}
		if (m_IsFalling && c->GetLabel() == "Enemy")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				Enemy* e = c->GetGameObject()->GetComponent<Enemy>();
				if (!e->GetKilled())
				{
					e->Kill();
				}
			}
		}
	}

	m_PrevOverlapPlatform = m_OverlapPlatform;
}

void BurgerPart::Fall(bool extendFall)
{
	if (m_IsFalling)
		return;

	if (extendFall)
	{
		++m_FallCounter;
	}

	if (m_PlayerFall && m_EnemiesOnPart > 0)
		AddEnemiesOnPartScore();

	m_pSubject->Notify(BTEvents::BurgerDropped);
	m_IsFalling = true;
	m_PlayerFall = false;
	m_HitPart = false;
	ResetSegments();
	FallOverlappingEnemies();
}

void BurgerPart::FallOverlappingEnemies()
{
	for (dae::Collider* c : m_Collider->GetColliders())
	{
		if (c == m_Collider)
			continue;

		if (m_IsFalling && c->GetLabel() == "Enemy")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				Enemy* e = c->GetGameObject()->GetComponent<Enemy>();
				if (!e->GetKilled())
				{
					e->Fall(this);
					++m_FallCounter;
					++m_EnemiesOnPart;
				}
			}
		}
	}
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

void BurgerPart::EnableStacking(bool enable)
{
	m_Stacking = enable; 
	m_FallCounter = 0;
}

void BurgerPart::AddEnemiesOnPartScore()
{
	m_pSubject->Notify(this, BTEvents::EnemiesDiedOnTop);
	m_EnemiesOnPart = 0;
}