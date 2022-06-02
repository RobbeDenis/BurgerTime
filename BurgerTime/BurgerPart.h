#pragma once
#include <BaseComponent.h>
#include <Collider.h>

enum class PartType
{
	TopBun = 0,
	BotBun = 1,
	Cheese = 2,
	Patty = 3,
	Tomato = 4,
	Lettuce = 5
};

class BurgerPart final : public dae::BaseComponent
{
public:
	void PostLoad() override;

	void SetType(PartType type);

private:
	BurgerPart(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	dae::Collider* m_Collider;
	PartType m_Type;
	int m_Width;
	int m_Height;

	float m_SrcX;
	float m_SrcY;
	float m_SrcH;
	float m_SrcW;
};
