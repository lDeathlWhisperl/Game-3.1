#pragma once

#include "Undead.h"

class Draugr : public Undead
{
public:
	Draugr() : Undead(10, 5, 5, 3) {}

	void draw()
	{
		std::cout << "\x1b[42m\x1b[30m" << level << "\x1b[0m";
	}
};