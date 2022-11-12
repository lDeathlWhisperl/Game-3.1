#pragma once

#include "Spirit.h"

class Ghoul : public Spirit
{
public:
	Ghoul() : Spirit(8, 7, 5, 3) {}

	void draw()
	{
		std::cout << "\x1b[100m\x1b[30m" << level << "\x1b[0m";
	}
};