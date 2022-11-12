#pragma once

#include "Spirit.h"

class Mummy : public Spirit
{
public:
	Mummy() : Spirit() 
	{
		level = 1;
	}

	void draw()
	{
		std::cout << "\x1b[103m\x1b[30m" << level << "\x1b[0m";
	}
};