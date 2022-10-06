#include <iostream>
#include <cmath>
#include <windows.h>
#include "Perlin.h"
#include "World.h"

//32 - tree
//92 - field

//34 - deep water
//94 - bright water
//36 - river

//93 - sand
//90 - stone
//33 - chest

void World::plantTree(int x, int y)
{
	highMap[y - 1][x] = 2;
	highMap[y][x - 1] = 2;
	highMap[y][x] = 2;
}

void World::landscape()
{
	for (int y = 0; y < width; y++)
	{
		std::vector<double> temp;
		for (int x = 0; x < length; x++)
			temp.push_back(0);
		highMap.push_back(temp);
	}
}

void World::generator(long long int seed, int x_index, int y_index)
{
	PerlinNoise pn(seed);
	landscape();

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
		{
			double t_x = (double)(x + x_index) / ((double)length);
			double t_y = (double)(y + y_index) / ((double)width);

			highMap[y][x] = pn.noise(3 * t_x, 3 * t_y, 600);

			if ((highMap[y][x] > 0.34 && highMap[y][x] <= 0.5 || highMap[y][x] >= 0.546) && y > 0 && y < width - 1 && x > 0 && x < length - 1)
				if (pn.noise(222 * t_x, 222 * t_y, 600) >= 0.38 && pn.noise(222 * t_x, 222 * t_y, 600) <= 0.45)
					plantTree(x,y);
		}
}

std::string World::paint(double high)
{
	std::string res;

	if(high <= 0.2)
		res = "\x1b[34m";				//deep water
	else if(high > 0.2 && high <= 0.3)
		res = "\x1b[94m";				//bright water
	else if (high > 0.3 && high <= 0.34)
		res = "\x1b[93m";				//sand
	else if(high > 0.5 && high <= 0.545)
		res = "\x1b[36m";				//river
	else
		res = "\x1b[92m";               //field

	if(high == 2)
		res = "\x1b[32m";				//tree

	res += tile;
	res += "\x1b[0m";
	return res;
}

void World::draw()
{
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < length; x++)
			std::cout << paint(highMap[y][x]);
		std::cout << '\n';
	}
}

void World::clean()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}