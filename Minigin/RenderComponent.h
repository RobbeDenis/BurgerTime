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
		void SetDst(const float x, const float y, const float width, const float height);
		void SetSrc(const float x, const float y, const float width, const float height);
		void UseSrc(bool use) { m_UseSrc = use; };
		void Mirror(bool mirror) { m_Mirrored = mirror; };

		void Render() const;


	private:
		RenderComponent(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		std::shared_ptr<Texture2D> m_Texture2D{};
		SDL_Rect m_SrcRect;
		SDL_Rect m_DstRect;
		bool m_UseSrc;
		bool m_UseDst;
		bool m_Mirrored;
	};
}

