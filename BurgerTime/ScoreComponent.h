#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class ScoreComponent : public BaseComponent, public Observer
	{
	public:
		void PostLoad() override;

		void Notify(Event event) override;
		void Notify(BaseComponent*, Event event) override { Notify(event); };

		void SetColor(const SDL_Color& color);

	private:
		ScoreComponent(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		void EnemyDied();
		void BurgerDropped();
		void ResetScore();
		void CheckIfGameWon();

		TextComponent* m_pTextPoints = nullptr;
		int m_ScoreToWin = 500;
		int m_BaseKillValue = 40;
		int m_KillValue = 40;
		int m_BurgerValue = 30;
		int m_Score = 0;
	};
}

