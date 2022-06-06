#pragma once
#include <Singleton.h>
#include <vector>
#include "Character.h"

class RespawnManager final : public dae::Singleton<RespawnManager>
{
public:
	void AddChar(Character* c)
	{
		m_Characters.push_back(c);
	}

	void Respawn()
	{
		for (Character* c : m_Characters)
			c->Respawn();
	}

private:
	std::vector<Character*> m_Characters;
};
