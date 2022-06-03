#pragma once
#include "Character.h"

class PeterPepper final : public Character
{
public:
	void PostLoad() override;
	void Start() override;
	void Update() override;

	int GetLives() const { return m_Lives; };
	void Kill() override;

private:
	PeterPepper(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void Die();

	int m_Lives;
	float m_MaxDeathTime;
	float m_DeathTime;
};


