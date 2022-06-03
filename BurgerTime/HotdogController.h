#pragma once
#include <BaseComponent.h>
class HotdogController final : public dae::BaseComponent
{
public:

private:
	HotdogController(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();
};

