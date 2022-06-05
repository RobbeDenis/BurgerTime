#pragma once
#include <Observer.h>

class GameManager final : public dae::Observer
{
public:
	GameManager();
	~GameManager();

	void Notify(int event) override;
	void Notify(dae::BaseComponent*, int event) override { Notify(event); };

	const std::string& GetSinglePlayerName() const { return m_SinglePlayer; };
	const std::string& GetCoopName() const { return m_Coop; };
	const std::string& GetVersusName() const { return m_Versus; };

private:
	void ResetLevel();

	const std::string m_SinglePlayer = "SinglePlayer";
	const std::string m_Coop = "Coop";
	const std::string m_Versus = "Versus";
};

