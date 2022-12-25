#pragma once

#include "AI.h"

class Spirit : public AI
{
public:
	Spirit() : AI() 
	{
		level = 1;
	}

	Spirit(int hp, int arm, int str, int lvl) : AI(hp, arm, str)
	{
		level = lvl;
	}

	~Spirit() {}
};