#pragma once
#include "BaseComponent.h"

namespace dae
{
	enum class Event
	{
		PlayerDied,
		PlayerReset,
		EnemyDied,
		BurgerDropped
	};

	class Observer;
	class Subject : public BaseComponent
	{
	public:
		void Notify(Event event);
		void Notify(BaseComponent* pComponent, Event event);

		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);

	private:
		Subject(GameObject* gameObject) : BaseComponent(gameObject) {};
		template <typename T>
		friend T* GameObject::AddComponent();

		std::vector<Observer*> m_pObservers{};
	};
}