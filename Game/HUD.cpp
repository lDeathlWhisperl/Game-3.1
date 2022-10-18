#include "HUD.h"

void HUD::frame()
{
	for (int i = 0; i < length; i++)
		std::cout << (unsigned char)219;
}

void HUD::healthBar(Player player)
{
	std::cout << (unsigned char)219;

	for (int i = 1; i < length - 1; i++)
		if (i <= player.getHP())
			std::cout << "\x1b[31m" << (unsigned char)219 << "\x1b[0m";
		else
			std::cout << ' ';

	std::cout << (unsigned char)219;
}

void HUD::armorBar(Player player)
{
	std::cout << (unsigned char)219;

	for (int i = 1; i < length - 1; i++)
		if (i <= player.getArmor())
			std::cout << "\x1b[32m" << (unsigned char)219 << "\x1b[0m";
		else
			std::cout << (unsigned char)219;


	std::cout << (unsigned char)219;
}

int HUD::getLength()
{
	return length;
}

void HUD::draw(Player player, int& x, int& y)
{
	if (x == 0 && (y == 0 || y == 3))
	{
		frame();
		x += getLength();
	}

	if (x == 0 && y == 1)
	{
		healthBar(player);
		x += getLength();
	}

	if (x == 0 && y == 2)
	{
		armorBar(player);
		x += getLength();
	}
}