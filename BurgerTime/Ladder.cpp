#include "Ladder.h"
#include <Collider.h>

Ladder::Ladder(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Width(0)
	, m_Height(0)
	, m_SnapRange(5)
{

}

void Ladder::SetDimensions(const int width, const int height)
{
	m_Width = width;
	m_Height = height;

	dae::Collider* c = m_pGameObject->GetComponent<dae::Collider>();

	if (c)
	{
		c->SetDimensions(m_Width, m_Height);
	}
}

bool Ladder::CanSnapToLadder(const glm::vec3& pos, const int width)
{

}
