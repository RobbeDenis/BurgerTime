#pragma once
#include <BaseComponent.h>
#include <Collider.h>
#include <Subject.h>

enum PartType
{
	TopBun = 0,
	BotBun = 1,
	Cheese = 2,
	Patty = 3,
	Tomato = 4,
	Lettuce = 5
};

class Enemy;

class BurgerPart final : public dae::BaseComponent
{
public:
	void PostLoad() override;
	void FixedUpdate() override;

	void AddObserver(dae::Observer* observer);

	void SetType(PartType type);
	PartType GetType() const { return m_Type; };
	int GetEnemiesOnTop() const { return m_EnemiesOnPart; };
	int GetFallCounter() const { return m_FallCounter; };

	void Fall(bool extendFall = false);
	void EnableStacking(bool enable);

private:
	BurgerPart(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void HandleOverlaps();
	void ResetSegments();
	void FallOverlappingEnemies();
	void AddEnemiesOnPartScore();

	std::vector<bool> m_Segments;
	int m_TotalSegments;

	std::shared_ptr<dae::Subject> m_pSubject;
	dae::Collider* m_Collider;
	PartType m_Type;
	int m_Width;
	int m_Height;
	float m_FallSpeed;
	int m_DisWalkedLeft;
	int m_FallCounter;
	int m_BounceHeight;
	int m_EnemiesOnPart;

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
	bool m_PlayerFall;
};

