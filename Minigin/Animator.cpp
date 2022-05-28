#include "RodEnginePCH.h"
#include "Animator.h"
#include "RenderComponent.h"

dae::Animator::Animator(GameObject* gameObject)
	: BaseComponent(gameObject)
{

}

void dae::Animator::PostLoad()
{
	m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();
}