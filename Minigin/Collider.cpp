#include "RodEnginePCH.h"
#include "Collider.h"
#include "Renderer.h"

std::vector<dae::Collider*> dae::Collider::g_Colliders;

dae::Collider::Collider(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Label("")
	, m_Rect{ 0,0,0,0 }
	, m_CalculateOverlaps(false)
{
	g_Colliders.push_back(this);
}

dae::Collider::~Collider()
{
	
}

void dae::Collider::FixedUpdate()
{
	if (!m_CalculateOverlaps)
		return;

	//m_PrevOverlaps = m_Overlaps;

	//for (dae::Collider* c : g_Colliders)
	//{

	//}
}

bool dae::Collider::IsOverlappingWith(Collider* other)
{
	SDL_Rect otherRect = other->m_Rect;

	if (m_Rect.x > otherRect.x + otherRect.w ||
		m_Rect.x + m_Rect.w < otherRect.x ||
		m_Rect.y > otherRect.y + otherRect.h ||
		m_Rect.y + m_Rect.h < otherRect.y)
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
