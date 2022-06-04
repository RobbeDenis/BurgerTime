#pragma once
#include <Command.h>
#include "Character.h"

// Peter Pepper inputs
// RIGHT
class IMoveRight final : public Command
{
public:
	IMoveRight(Character* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveRight();
	}

private:
	Character* m_pPeter = nullptr;
};

//LEFT
class IMoveLeft final : public Command
{
public:
	IMoveLeft(Character* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveLeft();
	}

private:
	Character* m_pPeter = nullptr;
};

//STOP
class IStopMove final : public Command
{
public:
	IStopMove(Character* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->StopMoving();
	}

private:
	Character* m_pPeter = nullptr;
};

//UP
class IMoveUpLadder final : public Command
{
public:
	IMoveUpLadder(Character* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveUpLadder();
	}

private:
	Character* m_pPeter = nullptr;
};

//DOWN
class IMoveDownLadder final : public Command
{
public:
	IMoveDownLadder(Character* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveDownLadder();
	}

private:
	Character* m_pPeter = nullptr;
};

class IUseAbility final : public Command
{
public:
	IUseAbility(Character* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->UseAbility();
	}

private:
	Character* m_pPeter = nullptr;
};
