#pragma once

#include <iostream>
#include "CreatureI.h"

class Archer : public CreatureI
{
public:
	
	void draw()
	{
		std::cout << 'A';
	}

	void get()
	{
		std::cout << HP << ' ' << armor << ' ' << damage << ' ' << status;
	}
};

class Crossbower : public Archer
{

};