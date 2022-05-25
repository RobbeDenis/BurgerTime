#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Subject;
	class PeterPepper final : public BaseComponent
	{
	public:
		void PostLoad() override;
		void Update() override;

		// FOR TESTING ASSIGNMENT
		void SetPlayer(bool firstPlayer);

		int GetLives() const { return m_Lives; };

	private:
		PeterPepper(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		void Die();

		Subject* m_pSubject = nullptr;
		int m_Lives = 3;
		// FOR TESTING ASSIGNMENT
		bool m_FirstPlayer = true;
	};
}

