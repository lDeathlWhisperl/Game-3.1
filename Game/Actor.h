#pragma once

constexpr auto dead = false;
constexpr auto alive = true;

class Actor
{
protected:
	int HP,
		armor,
		damage;

	bool status = alive;

	void virtual draw() = 0;

	void getDamage(int dmg)
	{
		HP = HP - dmg + armor;
		if (HP < 0)
			status = dead;
	}
};