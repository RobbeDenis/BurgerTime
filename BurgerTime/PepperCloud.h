#pragma once
#include <BaseComponent.h>
#include "Collider.h"
#include "Animator.h"

class PepperCloud final : public dae::BaseComponent
{
public:
	void PostLoad() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;

	void Activate();

private:
	PepperCloud(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	enum PepperState
	{
		Active = 0,
		Inactive = 1
	};

	dae::Animator* m_Animator;
	dae::Collider* m_Collider;
	float m_MaxActiveTime;
	float m_ActiveTime;
	int m_Width;
	int m_Height;
	bool m_Active;
	bool m_FirstFrame;
};

