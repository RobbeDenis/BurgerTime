#pragma once
#include "BaseComponent.h"

namespace dae
{
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

	class Subject;
	class Observer;
	class Animator;
	class Collider;

	class PeterPepper final : public BaseComponent
	{
	public:
		void PostLoad() override;
		void Start() override;
		void Update() override;
		void AddObserver(Observer* observer);

		void MoveRight();
		void MoveLeft();
		void MoveUpLadder();
		void MoveDownLadder();
		void StopMoving();

		int GetLives() const { return m_Lives; };

		// FOR TESTING ASSIGNMENT
		void SetPlayer(bool firstPlayer);

	private:
		PeterPepper(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		void Die();
		void HandleMovement();

		std::shared_ptr<Subject> m_pSubject = nullptr;
		Animator* m_Animator;
		Collider* m_Collider;
		float m_Width;
		float m_Height;
		float m_MovementSpeed;
		int m_Lives;
		int m_State;
		bool m_PendingMove;


		// FOR TESTING ASSIGNMENT
		bool m_FirstPlayer = true;
	};
}

