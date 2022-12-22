#include "character.h"

void Character::getDamage(int dmg)
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

int Character::getMaxHP()
{
	return max_HP;
}

int Character::getHP()
{
	return HP;
}

int Character::getArmor()
{
	return armor;
}

int Character::attack()
{
	return strength;
}

bool Character::getStatus()
{
	return status;
}

int Character::getLevel()
{
	return level;
}

int Character::level_up()
{
	return ++level;
}