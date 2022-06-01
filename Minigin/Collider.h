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
	private:
		static std::vector<Collider*> g_Colliders;

	public:
		~Collider();

		void FixedUpdate() override;

		bool IsOverlappingWith(Collider* other);
		void EnableCalculateOverlaps(bool enable) { m_CalculateOverlaps = enable; };

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
		bool m_CalculateOverlaps;
	};
}

