#include "Platform.h"
#include <Collider.h>

Platform::Platform(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_VerticalSnapOffset(3)
	, m_Width(0)
	, m_Height(0)
{

}

void Platform::SetDimensions(const int width, const int height)
{
	m_Width = width;
	m_Height = height;

	dae::Collider* c = m_pGameObject->GetComponent<dae::Collider>();

	if (c)
	{
		c->SetDimensions(m_Width, m_Height);
	}
}

glm::vec3 Platform::CalculateClampedPos(const glm::vec3& pos, const int width)
{
	glm::vec3 newPos = pos;
	glm::vec3 platPos = m_pGameObject->GetWorldPosition();

	if (pos.x < platPos.x)
	{
		newPos.x = platPos.x;
	}
	else if (pos.x + width > platPos.x + m_Width)
	{
		newPos.x = platPos.x + m_Width - width;
	}
	
	return newPos;
}

glm::vec3 Platform::CalculateSnappedPos(const glm::vec3& pos, const int height)
{
	glm::vec3 newPos;
	newPos.x = pos.x;
	newPos.y = m_pGameObject->GetWorldPosition().y + m_VerticalSnapOffset - height;
	newPos.z = pos.z;

	return newPos;
}
