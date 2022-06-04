#pragma once
#include "Character.h"

class PepperCloud;

class PeterPepper final : public Character
{
public:
	void PostLoad() override;
	void Start() override;
	void Update() override;

	int GetLives() const { return m_Lives; };
	void Kill() override;
	void UseAbility() override;
	void AddPepperCloud(PepperCloud* cloud) { m_PepperCloud = cloud; };


private:
	PeterPepper(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void Die();

	PepperCloud* m_PepperCloud;
	int m_Lives;
	float m_MaxDeathTime;
	float m_DeathTime;
	int m_PepperReach;
};


