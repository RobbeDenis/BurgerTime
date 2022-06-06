#include "HighScore.h"
#include "BTEvents.h"
#include "ScoreComponent.h"
#include <iostream>
#include <fstream>

HighScore::HighScore(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_HighScore(0)
	, m_File("../Data/Saves/Highscore.txt")
{

}

void HighScore::Reset()
{
	m_pTextPoints->SetText(std::to_string(m_HighScore));
}

void HighScore::PostLoad()
{
	m_pTextPoints = m_pGameObject->GetComponent<dae::TextComponent>();

	std::ifstream input;
	input.open(m_File, std::ios::in | std::ios::binary);
	if (input.is_open())
	{
		input.read((char*)&m_HighScore, sizeof(m_HighScore));
	}
	input.close();

	m_pTextPoints->SetText(std::to_string(m_HighScore));
}

void HighScore::SetColor(const SDL_Color& color)
{
	m_pTextPoints->SetColor(color);
}

void HighScore::SaveScore(const int score)
{
	if (score > m_HighScore)
	{
		m_HighScore = score;

		std::ofstream output;
		output.open(m_File, std::ios::out | std::ios::binary);
		if (output.is_open())
		{
			output.write((char*)&m_HighScore, sizeof(m_HighScore));
		}
		output.close();
	}
}
