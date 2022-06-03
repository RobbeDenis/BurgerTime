#pragma once
#include <BaseComponent.h>
#include <Collider.h>
#include <Subject.h>

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
	void FixedUpdate() override;

	void AddObserver(dae::Observer* observer);

	void SetType(PartType type);
	PartType GetType() const { return m_Type; };

	void Fall();
	void EnableStacking(bool enable) { m_Stacking = enable; };

private:
	BurgerPart(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void HandleOverlaps();

	std::shared_ptr<dae::Subject> m_pSubject;
	dae::Collider* m_Collider;
	PartType m_Type;
	int m_Width;
	int m_Height;
	float m_FallSpeed;

	float m_SrcX;
	float m_SrcY;
	float m_SrcH;
	float m_SrcW;

	bool m_OverlapPlatform;
	bool m_PrevOverlapPlatform;
	bool m_BeginOverlapPlatform;

	bool m_IsFalling;
	bool m_HitPart;

	bool m_Stacking;
};

