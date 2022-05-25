#pragma once
#include "BaseComponent.h"

namespace dae
{
	class SceneGraphTest final : public BaseComponent
	{
	public:
		void PostLoad() override;

	private:
		SceneGraphTest(GameObject* gameObject) : BaseComponent(gameObject) {};
		template <typename T>
		friend T* GameObject::AddComponent();
	};
}

