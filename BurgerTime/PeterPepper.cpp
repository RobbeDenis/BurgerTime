#include "PeterPepper.h"
#include <InputManager.h>
#include <ETime.h>
#include "BTEvents.h"
#include "PepperCloud.h"


PeterPepper::PeterPepper(dae::GameObject* gameObject)
	: Character(gameObject)
	, m_Lives(3)
	, m_MaxDeathTime(2.5f)
	, m_DeathTime(0.f)
	, m_PepperCloud(nullptr)
	, m_PepperReach(34)
	, m_PepperCount(0)
	, m_MaxPepper(5)
{
	m_PepperCount = m_MaxPepper;
}

void PeterPepper::PostLoad() 
{
	Character::PostLoad();

	dae::InputManager::GetInstance().AddController(0);
	m_pSubject->Notify(this, BTEvents::PlayerReset);

	const float animWalkSpeed = 0.05f;
	const float animLadderSpeed = 0.08f;
	const float animDeathSpeed = 0.13f;

	m_Animator = m_pGameObject->GetComponent<dae::Animator>();
	m_Animator->AddAnimation(CharacterState::Idle, 1, { 16,0 }, 16, 16);
	m_Animator->AddAnimation(CharacterState::WalkLeft, 3, { 48,0 }, 16, 16, false, animWalkSpeed);
	m_Animator->AddAnimation(CharacterState::WalkRight, 3, { 48,0 }, 16, 16, true, animWalkSpeed);
	m_Animator->AddAnimation(CharacterState::LadderDown, 3, { 0,0 }, 16, 16, false, animLadderSpeed);
	m_Animator->AddAnimation(CharacterState::LadderUp, 3, { 96,0 }, 16, 16, false, animLadderSpeed);
	m_Animator->AddAnimation(CharacterState::Death, 5, { 64,16 }, 16, 16, false, animDeathSpeed, false);

	m_MovementSpeed = 75.f;
}

void PeterPepper::Start()
{
	Character::Start();
	m_Animator->SetAnimation(CharacterState::Idle);
	m_Animator->SetDst({ 0,0 }, float(m_Width), float(m_Height));
}

void PeterPepper::Update()
{
	Character::Update();

	if (m_Killed)
	{
		m_DeathTime += dae::ETime::GetInstance().GetDeltaTime();
		if (m_DeathTime >= m_MaxDeathTime)
		{
			Respawn();
			m_DeathTime = 0.f;
		}
	}
}

void PeterPepper::Kill()
{
	if (m_Killed)
		return;

	Die();
}

void PeterPepper::Die()
{
	m_Killed = true;
	m_Animator->SetAnimation(CharacterState::Death);
	--m_Lives;
	m_pSubject->Notify(this, BTEvents::PlayerDied);
}

void PeterPepper::UseAbility()
{
	if (m_PepperCount <= 0)
		return;

	glm::vec3 newPos = m_pGameObject->GetWorldPosition();

	switch (m_State)
	{
		case CharacterState::WalkRight:
		{
			newPos.x += m_Width / 2 + m_PepperReach;
			break;
		}
		case CharacterState::WalkLeft:
		{
			newPos.x -= m_Width / 2 + m_PepperReach;
			break;
		}
		case CharacterState::LadderIdleUp:
		case CharacterState::LadderUp:
		{
			newPos.y -= m_PepperReach + m_Height / 2;
			break;
		}
		case CharacterState::LadderIdleDown:
		case CharacterState::LadderDown:
		{
			newPos.y += m_PepperReach + m_Height / 2;
			break;
		}
		default:
		{
			return;
		}
	}

	m_PepperCloud->GetGameObject()->SetWorldPosition(newPos);
	m_PepperCloud->Activate();
	--m_PepperCount;
	m_pSubject->Notify(this, BTEvents::PepperUsed);
}