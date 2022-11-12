#pragma once

#include "Character.h"
#include "AStar.hpp"

#include <iostream>

class AI : public Character
{
public:
	AI() : Character(1, 1, 1) {}

	AI(int hp, int arm, int str) : Character(hp, arm, str) {}

	void controller(int goal)
	{

	}

	virtual void draw() = 0 {}
};