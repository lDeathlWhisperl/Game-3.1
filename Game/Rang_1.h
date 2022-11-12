#pragma once

#include "Spawner.h"

class Rang_1 : public Spawner
{
public:
	Undead* spawn_undead()
	{
		return new Skeleton();
	}

	Demon* spawn_demon()
	{
		return new Imp();
	}

	Spirit* spawn_spirit()
	{
		return new Mummy();
	}
};