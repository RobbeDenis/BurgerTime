#pragma once
#include "BaseComponent.h"
#include <Observer.h>
#include "TextComponent.h"
#include "HighScore.h"

class Enemy;

class ScoreComponent : public dae::BaseComponent, public dae::Observer
{
public:
	void PostLoad() override;
	void Reset() override;

	void Notify(int event) override;
	void Notify(BaseComponent*, int event) override;

	void SetColor(const SDL_Color& color);
	int GetScore() const { return m_Score; };
	void AddHighScore(HighScore* highscore) { m_HighScore = highscore; };

private:
	ScoreComponent(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void EnemyDied(BaseComponent* enemy);
	void BurgerDropped();
	void ResetScore();
	void EnemiesOnTop(BaseComponent* burgerPart);

	HighScore* m_HighScore;
	dae::TextComponent* m_pTextPoints = nullptr;
	int m_BurgerValue = 50;
	int m_Score = 0;
	int m_BaseEnemyValue = 500;
};

