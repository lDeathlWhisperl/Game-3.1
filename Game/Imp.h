#pragma once

#include "Demon.h"

class Imp : public Demon
{
public:
	Imp() : Demon(5, 1, 1, 1) {}

	void draw()
	{
		std::cout << "\x1b[43m\x1b[30m" << level << "\x1b[0m";
	}
};