#pragma once
#include <BaseComponent.h>
#include "Subject.h"
#include "Collider.h"
#include "Animator.h"

enum CharacterState
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

struct OverlapData
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

class Character : public dae::BaseComponent
{
public:
	virtual ~Character() = default;

	virtual void PostLoad() override;
	virtual void Start() override;
	virtual void Update() override;

	virtual void MoveRight();
	virtual void MoveLeft();
	virtual void MoveUpLadder();
	virtual void MoveDownLadder();
	virtual void StopMoving();

	virtual void Kill() {};
	virtual void Respawn();

	int GetWidth() const { return m_Width; };
	int GetHeight() const { return m_Height; };
	bool GetKilled() const { return m_Killed; };

	Ladder* GetOverlappingLadder() const { return m_OverlappingLadder; };
	Platform* GetOverlappingPlatform() const { return m_OverlappingPlatform; };

	void AddObserver(dae::Observer* observer);

protected:
	Character(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void HandleMovement();
	void HandleOverlaps();
	void SnapToOverlappingPlatform();
	void SnapToOverlappingLadder();
	bool CanMoveOnLadder() const;
	bool CanMoveOnPlatform() const;

	glm::vec3 m_SpawnPos;
	OverlapData m_OverlapData;
	std::shared_ptr<dae::Subject> m_pSubject = nullptr;
	dae::Animator* m_Animator;
	dae::Collider* m_Collider;
	Ladder* m_OverlappingLadder;
	Platform* m_OverlappingPlatform;
	int m_Width;
	int m_Height;
	float m_MovementSpeed;
	int m_State;
	bool m_PendingMove;
	bool m_Killed;
	bool m_Active;
};

