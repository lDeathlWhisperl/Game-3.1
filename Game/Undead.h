#pragma once

#include "AI.h"

class Undead : public AI
{
public:
	Undead() : AI() 
	{
		level = 1;
	}

	Undead(int hp, int arm, int str, int lvl) : AI(hp, arm, str) 
	{
		level = lvl;
	}

	~Undead() {}
};