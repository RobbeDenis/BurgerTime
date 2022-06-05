#pragma once
#include "Character.h"

enum class EnemyType
{
	HotDog = 0,
	Pickle = 1,
	Egg = 2
};

class BurgerPart;

class Enemy final : public Character
{
	enum CharacterState
	{
		Idle = 0,
		WalkLeft = 1,
		WalkRight = 2,
		LadderUp = 3,
		LadderDown = 4,
		Death = 5,
		LadderIdleUp = 6,
		LadderIdleDown = 7,
		Stunned = 8
	};

public:
	void PostLoad() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;

	void Kill() override;
	void Stun();
	void Fall(BurgerPart* bP);

	void SetType(const EnemyType& type) { m_Type = type; };
	void SetValue(const int value) { m_Value = value; };
	int GetValue() const { return m_Value; };

private:
	Enemy(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	BurgerPart* m_FollowPart;
	EnemyType m_Type;
	float m_MaxRespawnTime;
	float m_RespawnTime;
	float m_MaxInactiveTime;
	float m_InactiveTime;
	float m_MaxStunnedTime;
	float m_StunnedTime;
	int m_Value;
	bool m_Falling;
	bool m_CanRespawn;
};

