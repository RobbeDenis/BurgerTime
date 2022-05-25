#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class PeterPepper;
	class TextComponent;
	class LivesComponent final : public BaseComponent, public Observer
	{
	public:
		void Notify(Event) override { };
		void Notify(BaseComponent* pComponent, Event event) override;

		void SetColor(const SDL_Color& color);

	private:
		LivesComponent(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		void PlayerDied(PeterPepper* peter);
		PeterPepper* m_pPeterPepper = nullptr;
		TextComponent* m_pTextLives = nullptr;
	};
}

