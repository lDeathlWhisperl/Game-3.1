#pragma once

#include "AStar.hpp"
#include "Player.h"

#include <iostream>
#include <vector>

class AI : public Character
{
protected:
	static AStar::Generator generator;

	static int count;

	int id = 0;

	bool canAttack = false;
public:
	AI() : Character(1, 0, 1), id(++count) {}
	
	AI(int hp, int arm, int str) : Character(hp, arm, str), id(++count) {}

	~AI();

	void controller(Player& player);

	static void collision(std::vector<int> walls, int width, int height);

	virtual void draw() = 0 {}


};