#pragma once
#include <BaseComponent.h>
#include "Subject.h"
#include "Collider.h"
#include "Animator.h"


enum PeterState
{
	Idle = 0,
	WalkLeft = 1,
	WalkRight = 2,
	LadderUp = 3,
	LadderDown = 4,
	Death = 5,
	LadderIdleUp = 6,
	LadderIdleDown = 7
};

struct PeterOverlapData
{
	bool EnterLadder;
	bool ExitLadder;
	bool LadderOverlap;
	bool WasOnLadder;

	bool EnterPlatform;
	bool ExitPlatform;
	bool PlatformOverlap;
	bool WasOnPlatform;
};

class Ladder;
class Platform;

class PeterPepper final : public dae::BaseComponent
{
public:
	void PostLoad() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void AddObserver(dae::Observer* observer);

	void MoveRight();
	void MoveLeft();
	void MoveUpLadder();
	void MoveDownLadder();
	void StopMoving();

	int GetLives() const { return m_Lives; };

	// FOR TESTING ASSIGNMENT
	void SetPlayer(bool firstPlayer);

private:
	PeterPepper(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void Die();
	void HandleOverlaps();
	void HandleMovement();
	void SnapToOverlappingPlatform();
	bool CanMoveOnLadder() const;

	PeterOverlapData m_OverlapData;
	std::shared_ptr<dae::Subject> m_pSubject = nullptr;
	dae::Animator* m_Animator;
	dae::Collider* m_Collider;
	Ladder* m_UsingLadder;
	Platform* m_UsingPlatform;
	int m_Width;
	int m_Height;
	float m_MovementSpeed;
	int m_Lives;
	int m_State;
	bool m_PendingMove;


	// FOR TESTING ASSIGNMENT
	bool m_FirstPlayer = true;
};


