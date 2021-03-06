#pragma once
#include <Command.h>
#include "Character.h"
#include "UIPointer.h"

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

class PointerUp final : public Command
{
public:
	PointerUp(UIPointer* pointer) : m_pPointer(pointer) {}

	void Execute() override
	{
		m_pPointer->Up();
	}

private:
	UIPointer* m_pPointer = nullptr;
};

class PointerDown final : public Command
{
public:
	PointerDown(UIPointer* pointer) : m_pPointer(pointer) {}

	void Execute() override
	{
		m_pPointer->Down();
	}

private:
	UIPointer* m_pPointer = nullptr;
};

class Confirmed final : public Command
{
public:
	Confirmed(UIPointer* pointer) : m_pPointer(pointer) {}

	void Execute() override
	{
		if(m_pPointer)
			m_pPointer->Confirm();
	}

private:
	UIPointer* m_pPointer = nullptr;
};
