#pragma once
#include "Character.h"

enum class EnemyType
{
	HotDog = 0,
	Pickle = 1,
	Egg = 2
};

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

	void Kill() override;

	void SetType(const EnemyType& type) { m_Type = type; };
	void SetValue(const int value) { m_Value = value; };
	int GetValue() const { return m_Value; };

private:
	Enemy(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	EnemyType m_Type;
	int m_Value;
};

