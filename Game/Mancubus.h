#pragma once

#include "Demon.h"

class Mancubus : public Demon
{
public:
	Mancubus() : Demon(15, 10, 8, 3) {}

	void draw()
	{
		std::cout << "\x1b[41m\x1b[30m" << level << "\x1b[0m";
	}
};