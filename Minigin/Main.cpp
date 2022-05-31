#include "RodEnginePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "RodEngine.h"

#pragma warning(push, 0)
#pragma warning(disable:4996)
#include <steam_api.h>
#pragma warning (pop)

#include "CSteamAchievements.h"


int main(int, char*[]) 
{
	//if (!SteamAPI_Init())
	//{
	//	std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
	//	return 1;
	//}
	//else
	//{
	//	CSteamAchievements::g_SteamAchievements = new CSteamAchievements(CSteamAchievements::g_Achievements, 4);
	//	std::cout << "Successfully initialized steam." << std::endl;
	//}

	dae::RodEngine engine;
	engine.Run();

	//SteamAPI_Shutdown();

	//if (CSteamAchievements::g_SteamAchievements)
	//	delete CSteamAchievements::g_SteamAchievements;

    return 0;
}