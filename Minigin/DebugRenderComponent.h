#pragma once
#include "BaseComponent.h"
namespace dae
{
	class DebugRenderComponent final : public BaseComponent
	{
	public:
		void PostLoad() override;
		void Render() const;

		void SetDimensions(const int width, const int height);
		void SetColor(const SDL_Color& color);

	private:
		DebugRenderComponent(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		SDL_Color m_Color;
		int m_Width;
		int m_Height;
	};
}

