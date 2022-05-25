#pragma once
#include "BaseComponent.h"

namespace dae
{
	class SoundSystem;
	class SoundTest final : public BaseComponent
	{
	public:
		void PostLoad() override;
		void Update() override;

	private:
		SoundTest(GameObject* gameObject) : BaseComponent(gameObject) {};
		template <typename T>
		friend T* GameObject::AddComponent();

		float m_Volume = 0.5f;
		bool m_FirstFrame = true;
	};
}

