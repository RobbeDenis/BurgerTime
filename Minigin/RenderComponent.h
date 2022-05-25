#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class RenderComponent final : public BaseComponent
	{
	public:
		void PostLoad() override;

		void SetTexture(std::shared_ptr<Texture2D> texture2D);
		void SetTexture(const std::string& filename);

		void Render() const;


	private:
		RenderComponent(GameObject* gameObject) : BaseComponent(gameObject) {};
		template <typename T>
		friend T* GameObject::AddComponent();

		std::shared_ptr<Texture2D> m_Texture2D{};
	};
}

