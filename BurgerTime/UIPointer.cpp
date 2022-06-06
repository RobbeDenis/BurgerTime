#include "UIPointer.h"
#include <RenderComponent.h>
#include "BTEvents.h"

UIPointer::UIPointer(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Width(30)
	, m_Height(30)
	, m_Offset(40)
	, m_Index(0)
	, m_Max(3)
{
	m_pSubject = std::make_shared<dae::Subject>();
}

void UIPointer::PostLoad()
{
	m_StartPos = m_pGameObject->GetWorldPosition();

	dae::RenderComponent* r = m_pGameObject->GetComponent<dae::RenderComponent>();
	r->SetDst(0.f, 0.f, float(m_Width), float(m_Height));
	r->SetTexture("Pointer.png");
}

void UIPointer::Up()
{
	--m_Index;
	if (m_Index < 0)
		m_Index = m_Max - 1;

	ReplacePointer();
}

void UIPointer::Down()
{
	++m_Index;
	m_Index %= m_Max;
	ReplacePointer();
}

void UIPointer::ReplacePointer()
{
	glm::vec3 newPos = m_StartPos;
	newPos.y += m_Index * m_Offset;
	m_pGameObject->SetWorldPosition(newPos);

	m_pSubject->Notify(BTEvents::UIIndexChanged);
}

void UIPointer::SetMax(const int max)
{
	m_Max = max;
}

void UIPointer::AddObserver(dae::Observer* observer)
{
	m_pSubject->AddObserver(observer);
}

void UIPointer::Confirm()
{
	m_pSubject->Notify(this, BTEvents::UIConfirmed);
}
