#include "RodEnginePCH.h"
#include "PeterPepper.h"
#include "InputManager.h"
#include "Subject.h"
#include "LivesComponent.h"
#include "TextComponent.h"
#include "Animator.h"
#include "ETime.h"
#include "Collider.h"
#include "DebugRenderComponent.h"

dae::PeterPepper::PeterPepper(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Lives(3)
	, m_Width(32.f)
	, m_Height(32.f)
	, m_State(PeterState::Idle)
	, m_PendingMove(false)
	, m_MovementSpeed(100.f)
{
	m_pSubject = std::make_shared<Subject>();
}

void dae::PeterPepper::PostLoad() 
{
	InputManager::GetInstance().AddController(0);
	m_pSubject->Notify(this, Event::PlayerReset);

	const float animWalkSpeed = 0.1f;
	const float animLadderSpeed = 0.08f;
	const float animDeathSpeed = 0.13f;

	m_Animator = m_pGameObject->GetComponent<Animator>();
	m_Animator->AddAnimation(PeterState::Idle, 1, { 16,0 }, 16, 16);
	m_Animator->AddAnimation(PeterState::WalkLeft, 3, { 48,0 }, 16, 16, false, animWalkSpeed);
	m_Animator->AddAnimation(PeterState::WalkRight, 3, { 48,0 }, 16, 16, true, animWalkSpeed);
	m_Animator->AddAnimation(PeterState::LadderDown, 3, { 0,0 }, 16, 16, false, animLadderSpeed);
	m_Animator->AddAnimation(PeterState::LadderUp, 3, { 96,0 }, 16, 16, false, animLadderSpeed);
	m_Animator->AddAnimation(PeterState::Death, 5, { 64,16 }, 16, 16, false, animDeathSpeed, false);

	m_Collider = m_pGameObject->GetComponent<Collider>();
	m_Collider->SetDimensions(int(m_Width), int(m_Height));

	// DEBUG
	DebugRenderComponent* debugRender = m_pGameObject->GetComponent<DebugRenderComponent>();
	debugRender->SetDimensions(int(m_Width), int(m_Height));
	debugRender->SetColor({ 0, 255, 0, 255 });
}

void dae::PeterPepper::Start()
{
	m_Animator->SetAnimation(PeterState::Death);
	m_Animator->SetDst({ 0,0 }, m_Width, m_Height);
}

void dae::PeterPepper::FixedUpdate()
{
	HandleOverlaps();
}

void dae::PeterPepper::Update()
{
	HandleMovement();
}

void dae::PeterPepper::HandleOverlaps()
{
	for (Collider* c : m_Collider->GetColliders())
	{
		if (c == m_Collider)
			continue;

		if (c->GetLabel() == "Ladder")
		{
			if(Collider::IsOverlappingWith(c, m_Collider))
				std::cout << "Ladder overlap" << std::endl;
		}
		else if (c->GetLabel() == "Platform")
		{
			if (Collider::IsOverlappingWith(c, m_Collider))
				std::cout << "Platform overlap" << std::endl;
		}
	}
}

void dae::PeterPepper::HandleMovement()
{
	if (!m_PendingMove)
		return;

	float elapsedTime = ETime::GetInstance().GetDeltaTime();
	float distance = elapsedTime * m_MovementSpeed;
	glm::vec3 newPos = m_pGameObject->GetWorldPosition();

	switch (m_State)
	{
	case PeterState::WalkRight:
	{
		newPos.x += distance;
		m_pGameObject->SetWorldPosition(newPos);
		break;
	}
	case PeterState::WalkLeft:
	{
		newPos.x -= distance;
		m_pGameObject->SetWorldPosition(newPos);
		break;
	}
	case PeterState::LadderUp:
	{
		newPos.y -= distance;
		m_pGameObject->SetWorldPosition(newPos);
		break;
	}
	case PeterState::LadderDown:
	{
		newPos.y += distance;
		m_pGameObject->SetWorldPosition(newPos);
		break;
	}
	default:
		break;
	}

	m_PendingMove = false;
}

void dae::PeterPepper::MoveRight()
{
	if (m_State != PeterState::WalkRight)
		m_Animator->SetAnimation(PeterState::WalkRight);

	m_State = PeterState::WalkRight;
	m_PendingMove = true;

	//std::cout << "MoveRight" << std::endl;
}

void dae::PeterPepper::MoveLeft()
{
	if (m_State != PeterState::WalkLeft)
		m_Animator->SetAnimation(PeterState::WalkLeft);

	m_State = PeterState::WalkLeft;
	m_PendingMove = true;

	//std::cout << "MoveLeft" << std::endl;
}

void dae::PeterPepper::MoveUpLadder()
{
	if (m_State == PeterState::LadderIdleUp)
		m_Animator->Play();
	else if (m_State != PeterState::LadderUp)
		m_Animator->SetAnimation(PeterState::LadderUp);

	m_State = PeterState::LadderUp;
	m_PendingMove = true;

	//std::cout << "LadderUp" << std::endl;
}

void dae::PeterPepper::MoveDownLadder()
{
	if (m_State == PeterState::LadderIdleDown)
		m_Animator->Play();
	else if (m_State != PeterState::LadderDown)
		m_Animator->SetAnimation(PeterState::LadderDown);

	m_State = PeterState::LadderDown;
	m_PendingMove = true;

	//std::cout << "LadderDown" << std::endl;
}

void dae::PeterPepper::StopMoving()
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

void dae::PeterPepper::Die()
{
	--m_Lives;
	m_pSubject->Notify(this, Event::PlayerDied);
}

void dae::PeterPepper::AddObserver(Observer* observer)
{
	m_pSubject->AddObserver(observer);
}

// FOR TESTING ASSIGNMENT
void dae::PeterPepper::SetPlayer(bool firstPlayer)
{
	m_FirstPlayer = firstPlayer;
}