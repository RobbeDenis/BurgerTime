#pragma once
#include "BaseComponent.h"

namespace dae
{
	struct ColliderRect
	{
		float x, y, width, height;
	};

	class Collider final : public BaseComponent
	{
	public:
		void PostLoad() override;

		static bool IsOverlappingWith(Collider* c1, Collider* c2);
		const std::vector<Collider*>& GetColliders() const;

		void SetLabel(const std::string& label) { m_Label = label; };
		const std::string& GetLabel() const { return m_Label; };

		void SetDimensions(const int width, const int height);
		const SDL_Rect& GetRect();

	private:
		Collider(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		std::vector<Collider*> m_PrevOverlaps;
		std::vector<Collider*> m_Overlaps;

		SDL_Rect m_Rect;
		std::string m_Label;
	};
}

