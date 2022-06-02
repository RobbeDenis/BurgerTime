#pragma once
#include <Command.h>
#include "PeterPepper.h"

// Peter Pepper inputs
// RIGHT
class PeterMoveRight final : public Command
{
public:
	PeterMoveRight(PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveRight();
	}

private:
	PeterPepper* m_pPeter = nullptr;
};

//LEFT
class PeterMoveLeft final : public Command
{
public:
	PeterMoveLeft(PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveLeft();
	}

private:
	PeterPepper* m_pPeter = nullptr;
};

//STOP
class PeterStopMove final : public Command
{
public:
	PeterStopMove(PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->StopMoving();
	}

private:
	PeterPepper* m_pPeter = nullptr;
};

//UP
class PeterMoveUpLadder final : public Command
{
public:
	PeterMoveUpLadder(PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveUpLadder();
	}

private:
	PeterPepper* m_pPeter = nullptr;
};

//DOWN
class PeterMoveDownLadder final : public Command
{
public:
	PeterMoveDownLadder(PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveDownLadder();
	}

private:
	PeterPepper* m_pPeter = nullptr;
};
