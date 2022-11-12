#pragma once

#include "AI.h"

class Spirit : public AI
{
public:
	Spirit() : AI() {}

	Spirit(int hp, int arm, int str, int lvl) : AI(hp, arm, str)
	{
		level = lvl;
	}

	~Spirit() {}
};