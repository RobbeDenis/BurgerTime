#pragma once
#include "Subject.h"

namespace dae
{
	class BaseComponent;
	class Observer
	{
	public:
		virtual ~Observer() {};

		virtual void Notify(Event event) = 0;
		virtual void Notify(BaseComponent* pComponent, Event event) = 0;
	};
}