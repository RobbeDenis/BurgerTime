#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Animator final : public BaseComponent
	{
	public:

	private:
		Animator(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();
	};
}

