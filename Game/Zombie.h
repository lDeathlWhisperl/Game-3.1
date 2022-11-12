#pragma once

#include "Undead.h"

class Zombie : public Undead
{
public:
	Zombie() : Undead(5, 1, 2, 2) {}

	void draw()
	{
		std::cout << "\x1b[102m\x1b[30m" << level << "\x1b[0m";
	}
};