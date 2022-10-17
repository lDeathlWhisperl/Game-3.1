#include "Render.h"
//#include "World.h"

#include <iostream>
#include <windows.h>

std::string Render::paint(double high)
{
	std::string res;
	unsigned char tile = 219;

	if (high <= 0.2)
		res = "\x1b[34m";				//deep water
	else if (high > 0.2 && high <= 0.3)
		res = "\x1b[94m";				//bright water
	else if (high > 0.3 && high <= 0.34)
		res = "\x1b[93m";				//sand
	else if (high > 0.5 && high <= 0.545)
		res = "\x1b[36m";				//river
	else
		res = "\x1b[92m";               //field

	if (high == 2)
		res = "\x1b[32m";				//tree

	if (high == 3)
		res += "\x1b[93m";				//desert

	res += tile;
	res += "\x1b[0m";
	return res;
}

void Render::draw(World world)
{
	std::vector<std::vector<double>> map = world.getMap();
	for (int y = 0; y < world.y(); y++)
	{
		for (int x = 0; x < world.x(); x++)
			std::cout << paint(map[y][x]);
		std::cout << '\n';
	}
}

void Render::clean()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}