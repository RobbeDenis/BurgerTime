#include "PeterPepper.h"
#include "InputManager.h"
#include "LivesComponent.h"
#include "ETime.h"
#include "DebugRenderComponent.h"
#include "Platform.h"
#include "Ladder.h"

PeterPepper::PeterPepper(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Lives(3)
	, m_Width(32)
	, m_Height(32)
	, m_State(PeterState::Idle)
	, m_PendingMove(false)
	, m_MovementSpeed(100.f)
{
	m_pSubject = std::make_shared<dae::Subject>();
}

void PeterPepper::PostLoad() 
{
	dae::InputManager::GetInstance().AddController(0);
	m_pSubject->Notify(this, dae::Event::PlayerReset);

	const float animWalkSpeed = 0.1f;
	const float animLadderSpeed = 0.08f;
	const float animDeathSpeed = 0.13f;

	m_Animator = m_pGameObject->GetComponent<dae::Animator>();
	m_Animator->AddAnimation(PeterState::Idle, 1, { 16,0 }, 16, 16);
	m_Animator->AddAnimation(PeterState::WalkLeft, 3, { 48,0 }, 16, 16, false, animWalkSpeed);
	m_Animator->AddAnimation(PeterState::WalkRight, 3, { 48,0 }, 16, 16, true, animWalkSpeed);
	m_Animator->AddAnimation(PeterState::LadderDown, 3, { 0,0 }, 16, 16, false, animLadderSpeed);
	m_Animator->AddAnimation(PeterState::LadderUp, 3, { 96,0 }, 16, 16, false, animLadderSpeed);
	m_Animator->AddAnimation(PeterState::Death, 5, { 64,16 }, 16, 16, false, animDeathSpeed, false);

	m_Collider = m_pGameObject->GetComponent<dae::Collider>();
	m_Collider->SetDimensions(m_Width, m_Height);

	// DEBUG
	dae::DebugRenderComponent* debugRender = m_pGameObject->GetComponent<dae::DebugRenderComponent>();
	debugRender->SetDimensions(m_Width, m_Height);
	debugRender->SetColor({ 0, 255, 0, 255 });
}

void PeterPepper::Start()
{
	m_Animator->SetAnimation(PeterState::Death);
	m_Animator->SetDst({ 0,0 }, float(m_Width), float(m_Height));

	SnapToOverlappingPlatform();
}

void PeterPepper::FixedUpdate()
{

}

void PeterPepper::Update()
{

	HandleOverlaps();





	if (m_OverlapData.EnterPlatform)
		std::cout << "Plat Enter" << std::endl;

	if (m_OverlapData.ExitPlatform)
		std::cout << "Plat Exit" << std::endl;

	if (m_OverlapData.EnterLadder)
		std::cout << "Ladder Enter" << std::endl;

	if (m_OverlapData.ExitLadder)
		std::cout << "Ladder Exit" << std::endl;

	HandleMovement();
}

void PeterPepper::HandleOverlaps()
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

void PeterPepper::HandleMovement()
{
	if (!m_PendingMove)
		return;

	float elapsedTime = dae::ETime::GetInstance().GetDeltaTime();
	float distance = elapsedTime * m_MovementSpeed;
	glm::vec3 newPos = m_pGameObject->GetWorldPosition();

	switch (m_State)
	{
	case PeterState::WalkRight:
	{
		newPos.x += distance;
		newPos = m_UsingPlatform->CalculateClampedPos(newPos, m_Width);
		break;
	}
	case PeterState::WalkLeft:
	{
		newPos.x -= distance;
		newPos = m_UsingPlatform->CalculateClampedPos(newPos, m_Width);
		break;
	}
	case PeterState::LadderUp:
	{
		newPos.y -= distance;
		break;
	}
	case PeterState::LadderDown:
	{
		newPos.y += distance;
		break;
	}
	default:
		break;
	}

	m_pGameObject->SetWorldPosition(newPos);
	m_PendingMove = false;
}

void PeterPepper::SnapToOverlappingPlatform()
{
	HandleOverlaps();

	if (m_OverlapData.EnterPlatform)
	{
		glm::vec3 newPos = m_pGameObject->GetWorldPosition();
		newPos = m_UsingPlatform->CalculateSnappedPos(newPos, m_Height);
		newPos = m_UsingPlatform->CalculateClampedPos(newPos, m_Width);
		m_pGameObject->SetWorldPosition(newPos);
	}
	else
	{
		std::cout << "Peter did not start on a platform\n";
	}
}

bool PeterPepper::CanMoveOnLadder() const
{
	if (m_OverlapData.LadderOverlap)
	{
		return true;
	}
	return false;
}

void PeterPepper::MoveRight()
{
	if (m_State != PeterState::WalkRight)
		m_Animator->SetAnimation(PeterState::WalkRight);

	m_State = PeterState::WalkRight;
	m_PendingMove = true;

	//std::cout << "MoveRight" << std::endl;
}

void PeterPepper::MoveLeft()
{
	if (m_State != PeterState::WalkLeft)
		m_Animator->SetAnimation(PeterState::WalkLeft);

	m_State = PeterState::WalkLeft;
	m_PendingMove = true;

	//std::cout << "MoveLeft" << std::endl;
}

void PeterPepper::MoveUpLadder()
{
	if (!CanMoveOnLadder())
		return;

	if (m_State == PeterState::LadderIdleUp)
		m_Animator->Play();
	else if (m_State != PeterState::LadderUp)
		m_Animator->SetAnimation(PeterState::LadderUp);

	m_State = PeterState::LadderUp;
	m_PendingMove = true;

	//std::cout << "LadderUp" << std::endl;
}

void PeterPepper::MoveDownLadder()
{
	if (!CanMoveOnLadder())
		return;

	if (m_State == PeterState::LadderIdleDown)
		m_Animator->Play();
	else if (m_State != PeterState::LadderDown)
		m_Animator->SetAnimation(PeterState::LadderDown);

	m_State = PeterState::LadderDown;
	m_PendingMove = true;

	//std::cout << "LadderDown" << std::endl;
}

void PeterPepper::StopMoving()
{
	if (m_PendingMove)
		return;

	if (m_State == PeterState::LadderDown)
	{
		m_State = PeterState::LadderIdleDown;
		m_Animator->Pause();
	}
	else if (m_State == PeterState::LadderUp)
	{
		m_State = PeterState::LadderIdleUp;
		m_Animator->Pause();
	}
	else if (m_State == PeterState::WalkLeft || m_State == PeterState::WalkRight)
	{
		m_State = PeterState::Idle;
		m_Animator->SetAnimation(PeterState::Idle);
	}

	//std::cout << "StopMoving" << std::endl;
}

void PeterPepper::Die()
{
	--m_Lives;
	m_pSubject->Notify(this, dae::Event::PlayerDied);
}

void PeterPepper::AddObserver(dae::Observer* observer)
{
	m_pSubject->AddObserver(observer);
}

// FOR TESTING ASSIGNMENT
void PeterPepper::SetPlayer(bool firstPlayer)
{
	m_FirstPlayer = firstPlayer;
}