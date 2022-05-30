#include "RodEnginePCH.h"
#include "PeterPepper.h"
#include "InputManager.h"
#include "Subject.h"
#include "LivesComponent.h"
#include "TextComponent.h"
#include "Animator.h"

dae::PeterPepper::PeterPepper(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Lives(3)
	, m_Width(32.f)
	, m_Height(32.f)
{
	m_pSubject = std::make_shared<Subject>();
}

void dae::PeterPepper::PostLoad() 
{
	InputManager::GetInstance().AddController(0);
	m_pSubject->Notify(this, Event::PlayerReset);

	m_Animator = m_pGameObject->GetComponent<Animator>();
	m_Animator->AddAnimation(PeterState::Idle, 1, { 16,0 }, 16, 16);
	m_Animator->AddAnimation(PeterState::WalkLeft, 3, { 48,0 }, 16, 16);
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

void dae::PeterPepper::Update()
{
	if (m_FirstFrame)
	{
		m_Animator->SetAnimation(PeterState::Idle);
		m_Animator->SetDst({ 0,0 }, m_Width, m_Height);
		m_FirstFrame = false;
	}

	if (m_FirstPlayer) // FOR TESTING ASSIGNMENT
	{
		if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonDown))
			Die();

		if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonRight))
			m_pSubject->Notify(this, Event::EnemyDied);

		if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonLeft))
			m_pSubject->Notify(this, Event::BurgerDropped);
	}
	else
	{
		if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonA))
			Die();

		if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonB))
			m_pSubject->Notify(this, Event::EnemyDied);

		if (InputManager::GetInstance().IsPressed(XBox360Controller::ControllerButton::ButtonX))
			m_pSubject->Notify(this, Event::BurgerDropped);
	}
}

void dae::PeterPepper::Die()
{
	--m_Lives;
	m_pSubject->Notify(this, Event::PlayerDied);
}
