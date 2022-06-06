#pragma once
#include <Observer.h>

class UIPointer;

class GameManager final : public dae::Observer
{
public:
	GameManager();
	~GameManager();

	void Notify(int event) override;
	void Notify(dae::BaseComponent*, int event) override;

	const std::string& GetSinglePlayerName() const { return m_SinglePlayer; };
	const std::string& GetCoopName() const { return m_Coop; };
	const std::string& GetVersusName() const { return m_Versus; };
	const std::string& GetStartMenuName() const { return m_StartMenu; };
	const std::string& GetGameOverName() const { return m_GameOver; };
	const std::string& GetGameWonName() const { return m_GameWon; };

private:
	void ResetWholeScene();
	void ResetLevel();
	void GameOver();
	void GameWon();
	void PlateFilled();
	void Confirmed(UIPointer* p);

	const std::string m_SinglePlayer = "SinglePlayer";
	const std::string m_Coop = "Coop";
	const std::string m_Versus = "Versus";
	const std::string m_StartMenu = "StartMenu";
	const std::string m_GameOver = "GameOver";
	const std::string m_GameWon = "GameWon";

	int m_PlatesFilled;
	int m_MaxPlatesFilled;
	bool m_IsGameOver;
};

