#pragma once

#include "AI.h"

class Demon : public AI
{
public:
	Demon() : AI() {}

	Demon(int hp, int arm, int str, int lvl) : AI(hp, arm, str) 
	{
		level = lvl;
	}

	~Demon() {}
};