#include "RodEnginePCH.h"
#include "PeterPepper.h"
#include "InputManager.h"
#include "Subject.h"
#include "LivesComponent.h"
#include "TextComponent.h"

dae::PeterPepper::PeterPepper(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Lives(3)
{

}

void dae::PeterPepper::PostLoad() 
{
	InputManager::GetInstance().AddController(0);
	m_pSubject = m_pGameObject->GetComponent<Subject>();

	m_pSubject->Notify(this, Event::PlayerReset);
}

// FOR TESTING ASSIGNMENT
void dae::PeterPepper::SetPlayer(bool firstPlayer)
{
	m_FirstPlayer = firstPlayer;
}

void dae::PeterPepper::Update()
{
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
