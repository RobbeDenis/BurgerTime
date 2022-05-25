#pragma once
#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

#pragma warning(push, 0)
#pragma warning(disable:4996)
#include <steam_api.h>
#pragma warning (pop)

struct Achievement_t
{
	int m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};

// Defining our achievements
enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};

class CSteamAchievements
{
public:
	CSteamAchievements(Achievement_t* Achievements, int NumAchievements);
	~CSteamAchievements() = default;

	bool RequestStats();
	bool SetAchievement(const char* ID);

	STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
		m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
		m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
		UserAchievementStored_t, m_CallbackAchievementStored);

	// Achievement array which will hold data about the achievements and their state
	static Achievement_t g_Achievements[];

	static CSteamAchievements* g_SteamAchievements;

private:
	uint64 m_iAppID; // Our current AppID
	Achievement_t* m_pAchievements; // Achievements data
	int m_iNumAchievements; // The number of Achievements
	bool m_bInitialized; // Have we called Request stats and received the callback?
};

