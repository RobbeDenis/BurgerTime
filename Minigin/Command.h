#pragma once
#include <iostream>

class Command
{
public:
	Command() = default;
	virtual ~Command() {};
	virtual void Execute() = 0;
};



// DERIVED

class Fire final : public Command
{
	void Execute() override
	{
		std::cout << "Fire\n";
	}
};

class Duck final : public Command
{
	void Execute() override
	{
		std::cout << "Duck\n";
	}
};

class Jump final : public Command
{
	void Execute() override
	{
		std::cout << "Jump\n";
	}
};

class Fart final : public Command
{
	void Execute() override
	{
		std::cout << "Fart\n";
	}
};

