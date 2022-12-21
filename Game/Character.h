#pragma once

#include "Actor.h"

constexpr auto dead = false;
constexpr auto alive = true;

class Character : public Actor
{
protected:
	int HP       = 25,
		armor    = 5,
		strength = 0,
		max_HP   = 25,
		level    = 0, 
		money    = 0;

	char character = '\0';

	bool status = alive;

public:
	Character() {}

	Character(int hp, int arm, int str) : HP(hp), armor(arm), strength(str), max_HP(hp) {}

	void getDamage(int dmg)
	{
		if (armor > 0)
			armor--;
		else
			HP = HP - dmg;

		if (armor < 0)
			armor = 0;

		if (HP <= 0)
		{
			status = dead;
			character = 'X';
		}
	}

	int getMaxHP()
	{
		return max_HP;
	}

	int getHP()
	{
		return HP;
	}

	int getArmor()
	{
		return armor;
	}

	int attack()
	{
		return strength;
	}

	bool getStatus()
	{
		return status;
	}

	int getLevel()
	{
		return level;
	}

	int level_up()
	{
		return ++level;
	}
};