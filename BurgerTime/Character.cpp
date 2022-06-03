#include "Character.h"
#include <DebugRenderComponent.h>
#include <ETime.h>
#include "Platform.h"
#include "Ladder.h"

Character::Character(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Width(32)
	, m_Height(32)
	, m_State(CharacterState::Idle)
	, m_PendingMove(false)
	, m_MovementSpeed(100.f)
{
	m_pSubject = std::make_shared<dae::Subject>();
}

void Character::PostLoad()
{
	m_Collider = m_pGameObject->GetComponent<dae::Collider>();
	m_Collider->SetDimensions(m_Width, m_Height);

	// DEBUG
	dae::DebugRenderComponent* debugRender = m_pGameObject->GetComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(m_Width, m_Height);
	debugRender->SetColor({ 0, 255, 0, 255 });
}

void Character::Start()
{
	m_Animator->SetAnimation(CharacterState::Idle);
	m_Animator->SetDst({ 0,0 }, float(m_Width), float(m_Height));
	HandleOverlaps();
	SnapToOverlappingPlatform();
}

void Character::Update()
{
	HandleOverlaps();
	HandleMovement();
}

void Character::HandleMovement()
{
	if (!m_PendingMove)
		return;

	float elapsedTime = dae::ETime::GetInstance().GetDeltaTime();
	float distance = elapsedTime * m_MovementSpeed;
	glm::vec3 newPos = m_pGameObject->GetWorldPosition();

	switch (m_State)
	{
	case CharacterState::WalkRight:
	{
		newPos.x += distance;
		newPos = m_UsingPlatform->CalculateClampedPos(newPos, m_Width);
		break;
	}
	case CharacterState::WalkLeft:
	{
		newPos.x -= distance;
		newPos = m_UsingPlatform->CalculateClampedPos(newPos, m_Width);
		break;
	}
	case CharacterState::LadderUp:
	{
		newPos.y -= distance;
		newPos = m_UsingLadder->CalculateClampedPos(newPos, m_Height);
		break;
	}
	case CharacterState::LadderDown:
	{
		newPos.y += distance;
		newPos = m_UsingLadder->CalculateClampedPos(newPos, m_Height);
		break;
	}
	default:
		break;
	}

	m_pGameObject->SetWorldPosition(newPos);
	m_PendingMove = false;
}

void Character::HandleOverlaps()
{
	// Set data on false
	m_OverlapData.PlatformOverlap = false;
	m_OverlapData.LadderOverlap = false;

	for (dae::Collider* c : m_Collider->GetColliders())
	{
		if (c == m_Collider)
			continue;

		if (c->GetLabel() == "Ladder")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				// Is overlapping with ladder this frame
				m_OverlapData.LadderOverlap = true;
				m_UsingLadder = c->GetGameObject()->GetComponent<Ladder>();
			}
		}
		else if (c->GetLabel() == "Platform")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				// Is overlapping with platform this frame
				m_OverlapData.PlatformOverlap = true;
				m_UsingPlatform = c->GetGameObject()->GetComponent<Platform>();
			}
		}
	}

	// Platform setting data
	m_OverlapData.EnterPlatform = m_OverlapData.PlatformOverlap && !m_OverlapData.WasOnPlatform;
	m_OverlapData.ExitPlatform = m_OverlapData.WasOnPlatform && !m_OverlapData.PlatformOverlap;

	m_OverlapData.WasOnPlatform = m_OverlapData.PlatformOverlap;

	// Ladder setting data
	m_OverlapData.EnterLadder = m_OverlapData.LadderOverlap && !m_OverlapData.WasOnLadder;
	m_OverlapData.ExitLadder = m_OverlapData.WasOnLadder && !m_OverlapData.LadderOverlap;

	m_OverlapData.WasOnLadder = m_OverlapData.LadderOverlap;

}

void Character::SnapToOverlappingPlatform()
{
	if (!m_UsingPlatform)
		return;

	glm::vec3 newPos = m_pGameObject->GetWorldPosition();
	newPos = m_UsingPlatform->CalculateSnappedPos(newPos, m_Height);
	newPos = m_UsingPlatform->CalculateClampedPos(newPos, m_Width);
	m_pGameObject->SetWorldPosition(newPos);
}

void Character::SnapToOverlappingLadder()
{
	if (!m_UsingLadder)
		return;

	if (m_State == CharacterState::Idle ||
		m_State == CharacterState::WalkLeft ||
		m_State == CharacterState::WalkRight)
	{
		glm::vec3 newPos = m_pGameObject->GetWorldPosition();
		newPos = m_UsingLadder->CalculateSnappedPos(newPos, m_Width);
		m_pGameObject->SetWorldPosition(newPos);
	}
}

bool Character::CanMoveOnLadder() const
{
	if (m_OverlapData.LadderOverlap)
	{
		return m_UsingLadder->CanSnapToLadder(m_pGameObject->GetWorldPosition(), m_Width);
	}
	return false;
}

bool Character::CanMoveOnPlatform() const
{
	if (m_OverlapData.PlatformOverlap)
	{
		return m_UsingPlatform->CanSnapToPlatform(m_pGameObject->GetWorldPosition(), m_Height);
	}
	return false;
}

void Character::MoveRight()
{
	if (!CanMoveOnPlatform())
		return;

	SnapToOverlappingPlatform();

	if (m_State != CharacterState::WalkRight)
		m_Animator->SetAnimation(CharacterState::WalkRight);

	m_State = CharacterState::WalkRight;
	m_PendingMove = true;
}

void Character::MoveLeft()
{
	if (!CanMoveOnPlatform())
		return;

	SnapToOverlappingPlatform();

	if (m_State != CharacterState::WalkLeft)
		m_Animator->SetAnimation(CharacterState::WalkLeft);

	m_State = CharacterState::WalkLeft;
	m_PendingMove = true;
}

void Character::MoveUpLadder()
{
	if (!CanMoveOnLadder())
		return;

	SnapToOverlappingLadder();

	if (m_State == CharacterState::LadderIdleUp)
		m_Animator->Play();
	else if (m_State != CharacterState::LadderUp)
		m_Animator->SetAnimation(CharacterState::LadderUp);

	m_State = CharacterState::LadderUp;
	m_PendingMove = true;
}

void Character::MoveDownLadder()
{
	if (!CanMoveOnLadder())
		return;

	SnapToOverlappingLadder();

	if (m_State == CharacterState::LadderIdleDown)
		m_Animator->Play();
	else if (m_State != CharacterState::LadderDown)
		m_Animator->SetAnimation(CharacterState::LadderDown);

	m_State = CharacterState::LadderDown;
	m_PendingMove = true;
}

void Character::StopMoving()
{
	if (m_PendingMove)
		return;

	if (m_State == CharacterState::LadderDown)
	{
		m_State = CharacterState::LadderIdleDown;
		m_Animator->Pause();
	}
	else if (m_State == CharacterState::LadderUp)
	{
		m_State = CharacterState::LadderIdleUp;
		m_Animator->Pause();
	}
	else if (m_State == CharacterState::WalkLeft || m_State == CharacterState::WalkRight)
	{
		m_State = CharacterState::Idle;
		m_Animator->SetAnimation(CharacterState::Idle);
	}
}

void Character::AddObserver(dae::Observer* observer)
{
	m_pSubject->AddObserver(observer);
}