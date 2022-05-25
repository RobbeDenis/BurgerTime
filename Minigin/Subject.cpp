#include "RodEnginePCH.h"
#include "Subject.h"
#include "Observer.h"

void dae::Subject::Notify(Event event)
{
	for (Observer* observer : m_pObservers)
	{
		observer->Notify(event);
	}
}

void dae::Subject::Notify(BaseComponent* pComponent, Event event)
{
	for (Observer* observer : m_pObservers)
	{
		observer->Notify(pComponent, event);
	}
}

void dae::Subject::AddObserver(Observer* pObserver)
{
	auto it = std::find(begin(m_pObservers), end(m_pObservers), pObserver);
	if (it != end(m_pObservers))
		return;

	m_pObservers.push_back(pObserver);
}

void dae::Subject::RemoveObserver(Observer* pObserver)
{
	m_pObservers.erase(std::remove(begin(m_pObservers), end(m_pObservers), pObserver));
}
