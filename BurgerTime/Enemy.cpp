#include "Enemy.h"
#include "BTEvents.h"

Enemy::Enemy(dae::GameObject* gameObject)
	: Character(gameObject)
	, m_Type(EnemyType::HotDog)
{

}

void Enemy::PostLoad()
{
	Character::PostLoad();

	const float baseY = 32.f;
	const float animSpeed = 0.1f;

	m_Animator = m_pGameObject->GetComponent<dae::Animator>();
	m_Animator->AddAnimation(CharacterState::Idle, 1, { 0, 32 + baseY * int(m_Type) }, 16, 16);
	m_Animator->AddAnimation(CharacterState::WalkLeft, 2, { 32, 32 + baseY * int(m_Type) }, 16, 16, false, animSpeed);
	m_Animator->AddAnimation(CharacterState::WalkRight, 2, { 32, 32 + baseY * int(m_Type) }, 16, 16, true, animSpeed);
	m_Animator->AddAnimation(CharacterState::LadderDown, 2, { 0, 32 + baseY * int(m_Type) }, 16, 16, false, animSpeed);
	m_Animator->AddAnimation(CharacterState::LadderUp, 2, { 64, 32 + baseY * int(m_Type) }, 16, 16, false, animSpeed);
	m_Animator->AddAnimation(CharacterState::Death, 4, { 0, 48 + baseY * int(m_Type) }, 16, 16, false, 0.25f, false);
	m_Animator->AddAnimation(CharacterState::Stunned, 2, { 64, 48 + baseY * int(m_Type) }, 16, 16);

	m_MovementSpeed = 50.f;
}

void Enemy::Start()
{
	Character::Start();
	m_Animator->SetAnimation(CharacterState::Idle);
	m_Animator->SetDst({ 0,0 }, float(m_Width), float(m_Height));
}

void Enemy::FixedUpdate()
{
	Character::FixedUpdate();

	for (dae::Collider* c : m_Collider->GetColliders())
	{
		if (c == m_Collider)
			continue;

		if (c->GetLabel() == "Player")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				Character* player = c->GetGameObject()->GetComponent<Character>();
				player->Kill();
			}
		}
	}
}

void Enemy::Kill()
{
	if (m_Killed)
		return;

	m_pSubject->Notify(this, BTEvents::EnemyDied);
	m_Animator->SetAnimation(CharacterState::Death);
	m_Killed = true;
}
