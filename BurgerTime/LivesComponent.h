#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <RenderComponent.h>


class PeterPepper;

class LivesComponent final : public dae::BaseComponent, public dae::Observer
{
public:
	void PostLoad() override;

	void Notify(int) override { };
	void Notify(BaseComponent* pComponent, int event) override;

	void SetMaxLives(const int lives);

private:
	LivesComponent(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void PlayerDied(PeterPepper* peter);
	
	std::vector<dae::RenderComponent*> m_RenderComponents;
	int m_Offset;
	int m_Width;
	int m_Height;
};

