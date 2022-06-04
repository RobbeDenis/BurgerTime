#include "Enemy.h"
#include "BTEvents.h"
#include "BurgerPart.h"
#include <ETime.h>

Enemy::Enemy(dae::GameObject* gameObject)
	: Character(gameObject)
	, m_Type(EnemyType::HotDog)
	, m_Falling(false)
	, m_FollowPart(nullptr)
	, m_Value(0)
	, m_MaxRespawnTime(2.f)
	, m_RespawnTime(0.f)
	, m_CanRespawn(false)
{

}

void Enemy::PostLoad()
{
	Character::PostLoad();

	const float baseY = 32.f;
	const float animSpeed = 0.1f;
	const float animDeathSpeed = 0.08f;

	m_Animator = m_pGameObject->GetComponent<dae::Animator>();
	m_Animator->AddAnimation(CharacterState::Idle, 1, { 0, 32 + baseY * int(m_Type) }, 16, 16);
	m_Animator->AddAnimation(CharacterState::WalkLeft, 2, { 32, 32 + baseY * int(m_Type) }, 16, 16, false, animSpeed);
	m_Animator->AddAnimation(CharacterState::WalkRight, 2, { 32, 32 + baseY * int(m_Type) }, 16, 16, true, animSpeed);
	m_Animator->AddAnimation(CharacterState::LadderDown, 2, { 0, 32 + baseY * int(m_Type) }, 16, 16, false, animSpeed);
	m_Animator->AddAnimation(CharacterState::LadderUp, 2, { 64, 32 + baseY * int(m_Type) }, 16, 16, false, animSpeed);
	m_Animator->AddAnimation(CharacterState::Death, 4, { 0, 48 + baseY * int(m_Type) }, 16, 16, false, animDeathSpeed, false);
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

	if (m_Falling)
	{
		glm::vec3 newPos = m_pGameObject->GetWorldPosition();
		newPos.y = m_FollowPart->GetGameObject()->GetWorldPosition().y - m_Height / 2;
		m_pGameObject->SetWorldPosition(newPos);

		if (m_FollowPart->GetFallCounter() <= 0)
		{
			m_pSubject->Notify(this, BTEvents::EnemyDied);
			m_Animator->SetAnimation(CharacterState::Death);
			m_Falling = false;
			m_CanRespawn = true;
		}
	}

	if (m_Killed)
		return;

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

void Enemy::Update()
{
	Character::Update();

	if (m_CanRespawn)
	{
		m_RespawnTime += dae::ETime::GetInstance().GetDeltaTime();
		if (m_RespawnTime >= m_MaxRespawnTime)
		{
			Respawn();
			m_CanRespawn = false;
			m_RespawnTime = 0.f;
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
	m_CanRespawn = true;
}

void Enemy::Fall(BurgerPart* bP)
{
	m_FollowPart = bP;
	m_Animator->Pause();
	m_Killed = true;
	m_Falling = true;
}
