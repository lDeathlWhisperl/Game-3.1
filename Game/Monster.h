#pragma once

#include "Rang_1.h"
#include "Rang_2.h"
#include "Rang_3.h"

int getRandomNumber(int min, int max)
{
	return min + rand() % (max - min + 1);
}

AI* spawn(int rang, int monster)
{
	Spawner* spawner;
	AI* ai;
	switch (rang)
	{
	case 1:
		spawner = new Rang_1;
		break;
	case 2:
		spawner = new Rang_2;
		break;
	default:
		spawner = new Rang_3;
	}

	switch (monster)
	{
	case 1:
		ai = spawner->spawn_undead();
		break;
	case 2:
		ai = spawner->spawn_demon();
		break;
	default:
		ai = spawner->spawn_spirit();
	}
	return ai;
}