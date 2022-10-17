#pragma once

#include <iostream>
#include "Actor.h"

class Archer : public Actor
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