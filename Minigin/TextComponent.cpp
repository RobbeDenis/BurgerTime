#include "RodEnginePCH.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include "Font.h"
#include "ResourceManager.h"



dae::TextComponent::TextComponent(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Color{255, 255, 255}
	, m_Text{"Text Component"}
{
	m_Font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
}

void dae::TextComponent::PostLoad()
{
	m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();

	if (m_pRenderComponent == nullptr)
	{
		std::cout << "Warning: dae::TextComponent::PostLoad() No render component attached to parent gameobject" << std::endl;
	}

	UpdateText();
}

void dae::TextComponent::SetText(const std::string& text, bool updateText)
{
	m_Text = text;
	
	if (updateText)
		UpdateText();
}

void dae::TextComponent::SetColor(const SDL_Color& color, bool updateText)
{
	m_Color = color;

	if(updateText)
		UpdateText();
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> font, bool updateText)
{
	m_Font = font;

	if(updateText)
		UpdateText();
}

void dae::TextComponent::UpdateText()
{
	if (m_pRenderComponent == nullptr)
		return;

	if (m_Text.empty())
		return;

	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	auto sharedTexture = std::make_shared<Texture2D>(texture);
	m_pRenderComponent->SetTexture(sharedTexture);
}
