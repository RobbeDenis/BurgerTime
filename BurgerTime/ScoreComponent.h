#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

class ScoreComponent : public dae::BaseComponent, public dae::Observer
{
public:
	void PostLoad() override;

	void Notify(int event) override;
	void Notify(BaseComponent*, int event) override { Notify(event); };

	void SetColor(const SDL_Color& color);

private:
	ScoreComponent(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void EnemyDied();
	void BurgerDropped();
	void ResetScore();
	void CheckIfGameWon();

	dae::TextComponent* m_pTextPoints = nullptr;
	int m_ScoreToWin = 500;
	int m_BaseKillValue = 40;
	int m_KillValue = 40;
	int m_BurgerValue = 30;
	int m_Score = 0;
};

