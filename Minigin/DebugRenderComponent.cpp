#include "RodEnginePCH.h"
#include "DebugRenderComponent.h"
#include "Renderer.h"
#include "Scene.h"

dae::DebugRenderComponent::DebugRenderComponent(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Width(0)
	, m_Height(0)
	, m_Color{255, 0, 0, 255}
{

}

void dae::DebugRenderComponent::PostLoad()
{
	m_pGameObject->GetScene()->AddDebugRenderComponent(this);
}

void dae::DebugRenderComponent::SetDimensions(const int width, const int height)
{
	m_Width = width;
	m_Height = height;
}

void dae::DebugRenderComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

void dae::DebugRenderComponent::Render() const
{
	const auto& pos = m_pGameObject->GetWorldPosition();

	SDL_Rect rect;
	rect.x = int(pos.x);
	rect.y = int(pos.y);
	rect.w = m_Width;
	rect.h = m_Height;

	Renderer::GetInstance().RenderRect(rect, m_Color);
}
