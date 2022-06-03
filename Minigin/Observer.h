#pragma once
#include "Subject.h"

namespace dae
{
	class BaseComponent;
	class Observer
	{
	public:
		virtual ~Observer() {};

		virtual void Notify(int event) = 0;
		virtual void Notify(BaseComponent* pComponent, int event) = 0;
	};
}