#pragma once

constexpr auto dead = false;
constexpr auto alive = true;

class Actor
{
protected:
	int HP = 25,
		armor = 5,
		strength = 0;
	int pos_x = 0,
		pos_y = 0;
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

	int getPos_x()
	{
		return pos_x;
	}

	int getPos_y()
	{
		return pos_y;
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