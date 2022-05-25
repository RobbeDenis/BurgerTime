#pragma once
#include "BaseComponent.h"

namespace dae
{
    class Font;
    class Texture2D;
    class RenderComponent;

    class TextComponent final : public BaseComponent
    {
    public:
        void PostLoad() override;

        void SetText(const std::string& text, bool updateText = true);
        void SetFont(std::shared_ptr<Font> font, bool updateText = true);
        void SetColor(const SDL_Color& color, bool updateText = true);

    private:
        TextComponent(GameObject* gameObject);
        template <typename T>
        friend T* GameObject::AddComponent();

        std::shared_ptr<Font> m_Font;
        std::shared_ptr<Texture2D> m_TextTexture;
        std::string m_Text;
        SDL_Color m_Color;
        RenderComponent* m_pRenderComponent;

        void UpdateText();
    };
}

