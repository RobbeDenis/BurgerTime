#include "RodEnginePCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Texture2D.h"

dae::RenderComponent::RenderComponent(GameObject* gameObject) 
	: BaseComponent(gameObject)
	, m_SrcRect{ 0,0,0,0 }
	, m_UseSrc{ false }
	, m_DstRect{ 0,0,0,0 }
{

}

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

void dae::RenderComponent::SetDst(const float x, const float y, const float width, const float height)
{
	m_DstRect.x = static_cast<int>(x);
	m_DstRect.y = static_cast<int>(y);
	m_DstRect.w = static_cast<int>(width);
	m_DstRect.h = static_cast<int>(height);
}

void dae::RenderComponent::SetSrc(const float x, const float y, const float width, const float height)
{	
	m_SrcRect.x = static_cast<int>(x);
	m_SrcRect.y = static_cast<int>(y);
	m_SrcRect.w = static_cast<int>(width);
	m_SrcRect.h = static_cast<int>(height);
}

void dae::RenderComponent::Render() const
{
	if (m_Texture2D == nullptr)
		return;

	const auto& pos = m_pGameObject->GetWorldPosition();

	if (m_UseSrc)
		Renderer::GetInstance().RenderTexture(*m_Texture2D, m_SrcRect, int(pos.x + m_DstRect.x), int(pos.y + m_DstRect.y), m_DstRect.w, m_DstRect.h);
	else
		Renderer::GetInstance().RenderTexture(*m_Texture2D, pos.x, pos.y);
}