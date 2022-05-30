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
		LadderDown = 4
	};

	class Subject;
	class Observer;
	class Animator;
	class PeterPepper final : public BaseComponent
	{
	public:
		void PostLoad() override;
		void Start() override;
		void Update() override;
		void AddObserver(Observer* observer);

		// FOR TESTING ASSIGNMENT
		void SetPlayer(bool firstPlayer);

		int GetLives() const { return m_Lives; };

	private:
		PeterPepper(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		void Die();

		std::shared_ptr<Subject> m_pSubject = nullptr;
		Animator* m_Animator;
		float m_Width;
		float m_Height;
		int m_Lives = 3;


		// FOR TESTING ASSIGNMENT
		bool m_FirstPlayer = true;
	};
}

