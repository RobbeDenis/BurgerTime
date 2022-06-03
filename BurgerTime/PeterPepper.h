#pragma once
#include "Character.h"

class PeterPepper final : public Character
{
public:
	void PostLoad() override;

	int GetLives() const { return m_Lives; };

private:
	PeterPepper(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void Die();

	int m_Lives;
};


