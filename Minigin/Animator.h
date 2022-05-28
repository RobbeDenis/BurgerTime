#pragma once
#include "BaseComponent.h"

namespace dae
{
	class RenderComponent;

	class Animator final : public BaseComponent
	{
	public:
		void PostLoad() override;

	private:
		Animator(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		RenderComponent* m_pRenderComponent;
	};
}

