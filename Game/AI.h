#pragma once

#include "AStar.hpp"
#include "Player.h"

#include <iostream>
#include <vector>

class AI : public Character
{
	static AStar::Generator generator;
public:
	AI() : Character(1, 0, 1) {}
	
	AI(int hp, int arm, int str) : Character(hp, arm, str) 
	{
		
	}

	void controller(Player& player);

	void collision(std::vector<int> walls, int width, int height);

	virtual void draw() = 0 {}
};