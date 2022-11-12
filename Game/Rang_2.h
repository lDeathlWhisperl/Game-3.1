#pragma once

#include "Spawner.h"

class Rang_2 : public Spawner
{
public:
	Undead* spawn_undead()
	{
		return new Zombie();
	}

	Demon* spawn_demon()
	{
		return new Possessed();
	}

	Spirit* spawn_spirit()
	{
		return new Gin();
	}
};