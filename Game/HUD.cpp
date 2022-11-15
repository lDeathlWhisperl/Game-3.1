#include "HUD.h"

void HUD::frame()
{
	for (int i = 0; i < length; i++)
		std::cout << (unsigned char)219;
}

void HUD::healthBar(Character* character)
{
	std::cout << (unsigned char)219;

	for (int i = 1; i < length - 1; i++)
		if (i <= character->getHP())
			std::cout << "\x1b[31m" << (unsigned char)219 << "\x1b[0m";
		else
			std::cout << ' ';

	std::cout << (unsigned char)219;
}

void HUD::armorBar(Character* character)
{
	std::cout << (unsigned char)219;

	for (int i = 1; i < length - 1; i++)
		if (i <= character->getArmor())
			std::cout << "\x1b[32m" << (unsigned char)219 << "\x1b[0m";
		else
			std::cout << (unsigned char)219;


	std::cout << (unsigned char)219;
}

int HUD::getLength()
{
	return length;
}

void HUD::addToViewport(Character* character, int& x, int& y, int pos_x, int pos_y)
{
	length = character->getMaxHP() + 2;
	if (x == pos_x && (y == pos_y || y == pos_y + 3))
	{
		frame();
		x += getLength();
	}

	if (x == pos_x && y == pos_y + 1)
	{
		healthBar(character);
		x += getLength();
	}

	if (x == pos_x && y == pos_y + 2)
	{
		armorBar(character);
		x += getLength();
	}
}