#include "PepperCloud.h"
#include <ETime.h>
#include <DebugRenderComponent.h>
#include "Enemy.h"

PepperCloud::PepperCloud(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Active(false)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_Height(32)
	, m_Width(32)
	, m_ActiveTime(0.f)
	, m_MaxActiveTime(0.6f)
	, m_FirstFrame(false)
{

}

void PepperCloud::PostLoad()
{
	m_Collider = m_pGameObject->GetComponent<dae::Collider>();
	m_Collider->SetDimensions(m_Width, m_Height);

	const float animSpeed = 0.05f;
	m_Animator = m_pGameObject->GetComponent<dae::Animator>();
	m_Animator->AddAnimation(PepperState::Active, 4, { 176, 16 }, 16, 16, false, animSpeed, false);
	m_Animator->AddAnimation(PepperState::Inactive, 1, { 160, 100 }, 16, 16, false, animSpeed, false);

	// DEBUG
	dae::DebugRenderComponent* debugRender = m_pGameObject->GetComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(m_Width, m_Height);
	debugRender->SetColor({ 0, 255, 0, 255 });
}

void PepperCloud::Start()
{
	m_Animator->SetAnimation(PepperState::Inactive);
	m_Animator->SetDst({ 0,0 }, float(m_Width), float(m_Height));
}

void PepperCloud::FixedUpdate()
{
	if (!m_FirstFrame)
		return;

	for (dae::Collider* c : m_Collider->GetColliders())
	{
		if (c == m_Collider)
			continue;

		if (c->GetLabel() == "Enemy")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				Enemy* e = c->GetGameObject()->GetComponent<Enemy>();
				e->Stun();
			}
		}
	}

	m_FirstFrame = false;
}

void PepperCloud::Update()
{
	if (m_Active)
	{
		m_ActiveTime += dae::ETime::GetInstance().GetDeltaTime();
		if (m_ActiveTime >= m_MaxActiveTime)
		{
			m_Active = false;
			m_ActiveTime = 0.f;
			m_Animator->SetAnimation(PepperState::Inactive);
		}
	}
}

void PepperCloud::Activate()
{
	m_Active = true;
	m_ActiveTime = 0.f;
	m_Animator->SetAnimation(PepperState::Active);
	m_FirstFrame = true;
}