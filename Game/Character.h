#pragma once

#include "Actor.h"

constexpr auto dead = false;
constexpr auto alive = true;

class Character : public Actor
{
protected:
	int HP = 25,
		armor = 5,
		strength = 0;

	bool status = alive;

public:
	void getDamage(int dmg)
	{
		if (armor > 0)
			armor--;
		else
			HP = HP - dmg;

		if (armor < 0)
			armor = 0;

		if (HP <= 0)
			status = dead;
	}

	int getHP()
	{
		return HP;
	}

	int getArmor()
	{
		return armor;
	}

	int getStrength()
	{
		return strength;
	}

	int getStatus()
	{
		return status;
	}
};