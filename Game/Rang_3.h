#pragma once

#include "Spawner.h"

class Rang_3 : public Spawner
{
	Undead* spawn_undead()
	{
		return new Draugr();
	}

	Demon* spawn_demon()
	{
		return new Mancubus();
	}

	Spirit* spawn_spirit()
	{
		return new Ghoul();
	}
};