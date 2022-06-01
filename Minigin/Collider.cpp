#include "RodEnginePCH.h"
#include "Collider.h"
#include "Renderer.h"

std::vector<dae::Collider*> dae::Collider::g_Colliders;

dae::Collider::Collider(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Label("")
	, m_Rect{ 0,0,0,0 }
{
	g_Colliders.push_back(this);
}

bool dae::Collider::IsOverlappingWith(Collider* c1, Collider* c2)
{
	SDL_Rect r1 = c1->GetRect();
	SDL_Rect r2 = c2->GetRect();

	if (r1.x > r2.x + r2.w ||
		r1.x + r1.w < r2.x ||
		r1.y > r2.y + r2.h ||
		r1.y + r1.h < r2.y)
	{
		return false;
	}

	return true;
}

void dae::Collider::SetDimensions(const int width, const int height)
{
	m_Rect.w = width;
	m_Rect.h = height;
}

const SDL_Rect& dae::Collider::GetRect()
{
	m_Rect.x = static_cast<int>(m_pGameObject->GetWorldPosition().x);
	m_Rect.y = static_cast<int>(m_pGameObject->GetWorldPosition().y);

	return m_Rect;
}
