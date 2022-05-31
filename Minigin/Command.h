#pragma once
#include <iostream>
#include "PeterPepper.h"

class Command
{
public:
	Command() = default;
	virtual ~Command() {};
	virtual void Execute() = 0;
};



// Peter Pepper inputs
// RIGHT
class PeterMoveRight final : public Command
{
public:
	PeterMoveRight(dae::PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveRight();
	}

private:
	dae::PeterPepper* m_pPeter = nullptr;
};

//LEFT
class PeterMoveLeft final : public Command
{
public:
	PeterMoveLeft(dae::PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveLeft();
	}

private:
	dae::PeterPepper* m_pPeter = nullptr;
};

//STOP
class PeterStopMove final : public Command
{
public:
	PeterStopMove(dae::PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->StopMoving();
	}

private:
	dae::PeterPepper* m_pPeter = nullptr;
};

//UP
class PeterMoveUpLadder final : public Command
{
public:
	PeterMoveUpLadder(dae::PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveUpLadder();
	}

private:
	dae::PeterPepper* m_pPeter = nullptr;
};

//DOWN
class PeterMoveDownLadder final : public Command
{
public:
	PeterMoveDownLadder(dae::PeterPepper* peter) : m_pPeter(peter) {}

	void Execute() override
	{
		m_pPeter->MoveDownLadder();
	}

private:
	dae::PeterPepper* m_pPeter = nullptr;
};
