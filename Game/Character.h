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

	void getDamage(int);

	int getMaxHP();

	int getHP();

	int getArmor();

	int attack();

	bool getStatus();

	int getLevel();

	int level_up();
};