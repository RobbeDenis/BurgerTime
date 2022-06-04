#pragma once
#include <BaseComponent.h>

class Character;
class Platform;
class Ladder;

class PickleController final : public dae::BaseComponent
{
public:
	void PostLoad() override;
	void FixedUpdate() override;
	void Update() override;

	void SetTarget(Character* target) { m_Target = target; };

private:
	PickleController(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	Character* m_Target;
	Character* m_Character;
	Platform* m_PrevPlatform;
	Ladder* m_PrevLadder;
	float m_MaxActivateDelay;
	float m_ActivateDelay;
	int m_WidthDetectOffset;
	int m_State;
	bool m_Active;
	bool m_UsingLadder;
};

