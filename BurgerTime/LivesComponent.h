#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"


class PeterPepper;

class LivesComponent final : public dae::BaseComponent, public dae::Observer
{
public:
	void PostLoad() override;

	void Notify(int) override { };
	void Notify(BaseComponent* pComponent, int event) override;

	void SetColor(const SDL_Color& color);

private:
	LivesComponent(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void PlayerDied(PeterPepper* peter);
	PeterPepper* m_pPeterPepper = nullptr;
	dae::TextComponent* m_pTextLives = nullptr;
};

