#include "Plate.h"

Plate::Plate(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Height(120)
	, m_Width(30)
	, m_Collider(nullptr)
{

}

void Plate::PostLoad()
{
	m_Collider = m_pGameObject->GetComponent<dae::Collider>();
	m_Collider->SetDimensions(m_Width, m_Height);
}
