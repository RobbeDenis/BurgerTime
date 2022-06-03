#pragma once
#include <BaseComponent.h>
class Enemy final : public dae::BaseComponent
{
public:

private:
	Enemy(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();
};

