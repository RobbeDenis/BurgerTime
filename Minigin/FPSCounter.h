#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;

	class FPSCounter final : public BaseComponent
	{
	public:
		void PostLoad() override;
		void Update() override;

		void UseSmoothing(bool enable);
		void SetUpdateInterval(float interval) { m_UpdateInterval = interval; };

	private:
		FPSCounter(GameObject* gameObject) : BaseComponent(gameObject) {};
		template <typename T>
		friend T* GameObject::AddComponent();

		TextComponent* m_pTextComponent = nullptr;
		float m_UpdateInterval = 0.679f;
		float m_ElapsedIntervalTime = 0.f;
		bool m_UseSmoothing = false;
	};
}

