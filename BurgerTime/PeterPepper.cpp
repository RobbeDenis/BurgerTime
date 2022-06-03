#include "PeterPepper.h"
#include <InputManager.h>
#include "BTEvents.h"


PeterPepper::PeterPepper(dae::GameObject* gameObject)
	: Character(gameObject)
	, m_Lives(3)
{
	
}

void PeterPepper::PostLoad() 
{
	Character::PostLoad();

	dae::InputManager::GetInstance().AddController(0);
	m_pSubject->Notify(this, BTEvents::PlayerReset);

	const float animWalkSpeed = 0.1f;
	const float animLadderSpeed = 0.08f;
	const float animDeathSpeed = 0.13f;

	m_Animator = m_pGameObject->GetComponent<dae::Animator>();
	m_Animator->AddAnimation(CharacterState::Idle, 1, { 16,0 }, 16, 16);
	m_Animator->AddAnimation(CharacterState::WalkLeft, 3, { 48,0 }, 16, 16, false, animWalkSpeed);
	m_Animator->AddAnimation(CharacterState::WalkRight, 3, { 48,0 }, 16, 16, true, animWalkSpeed);
	m_Animator->AddAnimation(CharacterState::LadderDown, 3, { 0,0 }, 16, 16, false, animLadderSpeed);
	m_Animator->AddAnimation(CharacterState::LadderUp, 3, { 96,0 }, 16, 16, false, animLadderSpeed);
	m_Animator->AddAnimation(CharacterState::Death, 5, { 64,16 }, 16, 16, false, animDeathSpeed, false);
}

void PeterPepper::Die()
{
	--m_Lives;
	m_pSubject->Notify(this, BTEvents::PlayerDied);
}