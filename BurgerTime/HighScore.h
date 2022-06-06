#pragma once
#include <BaseComponent.h>
#include <TextComponent.h>

class HighScore final : public dae::BaseComponent
{
public:
	void PostLoad() override;
	void Reset() override;

	void SaveScore(const int score);
	void SetColor(const SDL_Color& color);

private:
	HighScore(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	std::string m_File;
	dae::TextComponent* m_pTextPoints = nullptr;
	int m_HighScore;
};

