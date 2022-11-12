#pragma once

#include "Spirit.h"

class Gin : public Spirit
{
public:
	Gin() : Spirit(5, 1, 4, 2) {}

	void draw()
	{
		std::cout << "\x1b[106m\x1b[30m" << level << "\x1b[0m";
	}
};