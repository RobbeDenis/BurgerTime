#include "RodEnginePCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Texture2D.h"

void dae::RenderComponent::PostLoad()
{
	m_pGameObject->GetScene()->AddRenderComponent(this);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture2D)
{
	m_Texture2D = texture2D;
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture2D = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetBounds(const float x, const float y, const float width, const float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

void dae::RenderComponent::Render() const
{
	if (m_Texture2D == nullptr)
		return;

	const auto& pos = m_pGameObject->GetWorldPosition();

	if(m_UseBounds)
		Renderer::GetInstance().RenderTexture(*m_Texture2D, pos.x, pos.y);
	else
		Renderer::GetInstance().RenderTexture(*m_Texture2D, pos.x, pos.y);
}