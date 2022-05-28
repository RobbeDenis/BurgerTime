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
	class Subject final
	{
	public:
		void Notify(Event event);
		void Notify(BaseComponent* pComponent, Event event);

		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);

	private:
		std::vector<Observer*> m_pObservers{};
	};
}