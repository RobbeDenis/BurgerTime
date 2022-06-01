#pragma once
#include <iostream>

class Command
{
public:
	Command() = default;
	virtual ~Command() {};
	virtual void Execute() = 0;
};
