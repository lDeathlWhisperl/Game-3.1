#pragma once

#include "Undead.h"

class Skeleton : public Undead
{
public:
	Skeleton() : Undead() {};

	void draw()
	{
		std::cout << "\x1b[47m\x1b[30m" << level <<"\x1b[0m";
	}
};