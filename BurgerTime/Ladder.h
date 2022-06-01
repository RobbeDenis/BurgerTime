#pragma once
#include <BaseComponent.h>

class Ladder final : public dae::BaseComponent
{
public:

private:
	Ladder(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();
};

