#pragma once

#include "Demon.h"

class Possessed : public Demon
{
public:
	Possessed() : Demon(10, 4, 3, 2) {}

	void draw()
	{
		std::cout << level;
	}
};