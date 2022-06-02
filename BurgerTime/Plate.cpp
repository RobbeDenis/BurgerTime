#include "Plate.h"
#include "BurgerPart.h"

Plate::Plate(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Height(80)
	, m_Width(30)
	, m_Collider(nullptr)
{

}

void Plate::PostLoad()
{
	m_Collider = m_pGameObject->GetComponent<dae::Collider>();
	m_Collider->SetDimensions(m_Width, m_Height);
}

void Plate::FixedUpdate()
{
	for (dae::Collider* c : m_Collider->GetColliders())
	{
		if (c == m_Collider)
			continue;

		if (c->GetLabel() == "Burger")
		{
			if (dae::Collider::IsOverlappingWith(c, m_Collider))
			{
				BurgerPart* b = c->GetGameObject()->GetComponent<BurgerPart>();
				b->EnableStacking(true);
			}
		}
	}
}

bool Plate::CalculateClampedPos(glm::vec3& pos, const int height)
{
	glm::vec3 platePos = m_pGameObject->GetWorldPosition();

	if (pos.y + height >= platePos.y + m_Height)
	{
		pos.y = platePos.y + m_Height - height;
		return true;
	}

	return false;
}
