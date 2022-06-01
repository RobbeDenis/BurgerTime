#pragma once
#include <BaseComponent.h>

class Platform final : public dae::BaseComponent
{
public:

private:
	Platform(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();
};

