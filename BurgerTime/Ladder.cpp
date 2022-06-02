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

glm::vec3 Ladder::CalculateClampedPos(const glm::vec3& pos, const int height)
{
	glm::vec3 newPos = pos;
	glm::vec3 ladPos = m_pGameObject->GetWorldPosition();

	if (pos.y + height < ladPos.y)
	{
		newPos.y = ladPos.y - height;
	}
	else if (pos.y + height > ladPos.y + m_Height)
	{
		newPos.y = ladPos.y + m_Height - height;
	}

	return newPos;
}

glm::vec3 Ladder::CalculateSnappedPos(const glm::vec3& pos, const int width)
{
	glm::vec3 newPos = pos;
	newPos.x = (m_pGameObject->GetWorldPosition().x + float(m_Width / 2)) - float(width / 2);

	return newPos;
}

bool Ladder::CanSnapToLadder(const glm::vec3& pos, const int width)
{
	int otherMid = int(pos.x) + (width / 2);
	int thisMid = int(m_pGameObject->GetWorldPosition().x) + (m_Width / 2);

	return (abs(thisMid - otherMid) <= m_SnapRange);
}
