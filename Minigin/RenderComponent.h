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
		void SetBounds(const float x, const float y, const float width, const float height);
		void UseBounds(bool use) { m_UseBounds = use; };

		void Render() const;


	private:
		RenderComponent(GameObject* gameObject) : BaseComponent(gameObject) {};
		template <typename T>
		friend T* GameObject::AddComponent();

		std::shared_ptr<Texture2D> m_Texture2D{};
		float m_X;
		float m_Y;
		float m_Width;
		float m_Height;
		bool m_UseBounds;
	};
}

