#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Observer;
	class Subject final
	{
	public:
		void Notify(int event);
		void Notify(BaseComponent* pComponent, int event);

		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);

	private:
		std::vector<Observer*> m_pObservers{};
	};
}