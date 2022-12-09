#include "HUD.h"
#include <windows.h>

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

void HUD::addToViewport(Character* character)
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = pos_x;
	Position.Y = pos_y;
	SetConsoleCursorPosition(hOut, Position);

	int y;

	for (y = pos_y; y <= pos_y + 4; y++)
	{
		for (int x = pos_x; x < length + pos_x; x++)
		{
			if (x == pos_x && (y == pos_y || y == pos_y + 3))
				frame();

			else if (x == pos_x && y == pos_y + 1)
				healthBar(character);

			else if (x == pos_x && y == pos_y + 2)
				armorBar(character);
		}
		Position.X = pos_x;
		Position.Y = y+1;
		SetConsoleCursorPosition(hOut, Position);
	}
	length += pos_x;
	/*if (x == pos_x && (y == pos_y || y == pos_y + 3))
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
	}*/

}