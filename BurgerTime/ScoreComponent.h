#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

class Enemy;

class ScoreComponent : public dae::BaseComponent, public dae::Observer
{
public:
	void PostLoad() override;

	void Notify(int event) override;
	void Notify(BaseComponent*, int event) override;

	void SetColor(const SDL_Color& color);

private:
	ScoreComponent(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void EnemyDied(BaseComponent* enemy);
	void BurgerDropped();
	void ResetScore();
	void EnemiesOnTop(BaseComponent* burgerPart);

	dae::TextComponent* m_pTextPoints = nullptr;
	int m_BurgerValue = 50;
	int m_Score = 0;
	int m_BaseEnemyValue = 500;
};

