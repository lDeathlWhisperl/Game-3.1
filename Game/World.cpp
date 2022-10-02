#include <iostream>
#include <cmath>
#include "World.h"

//32 - tree
//92 - field

//34 - deep water
//94 - bright water

//93 - sand
//90 - castle
//33 - chest

int random(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void World::plantTree(int x, int y)
{
	polygons[y - 1][x] = 1;
	polygons[y][x - 1] = 1;
	polygons[y][x] = 1;
	polygons[y][x + 1] = 1;
	polygons[y + 1][x] = 1;
}

void World::landscape()
{
	for (size_t y = 0; y < width; y++)
	{
		std::vector<int> temp;
		for (size_t x = 0; x < length; x++)
			temp.push_back(0);
		polygons.push_back(temp);
	}
}

void World::smooth()
{
	for (int y = 1; y < width - 1; y++)
		for (int x = 1; x < length - 1; x++)
			polygons[y][x] = (
				polygons[y - 1][x - 1] + polygons[y - 1][x] + polygons[y - 1][x + 1] +
				polygons[y][x - 1] + polygons[y][x] + polygons[y][x + 1] +
				polygons[y + 1][x - 1] + polygons[y + 1][x] + polygons[y + 1][x + 1]) / 9;
}

void World::generator()
{
	srand(static_cast<unsigned int>(time(0)));
	landscape();

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
			if (random(0, 10) <= 2)
				polygons[y][x] = 1;

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
			if (random(0, 10) <= 8)
				polygons[y][x] = 4;

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
			polygons[y][x] += cos(25 * polygons[y][x] * 180 / 3.14) + cos(25 * polygons[y][x] * 180 / 3.14) * 25;

	smooth();

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
			polygons[y][x] += -1;

	smooth();

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
			if (polygons[y][x] > -4)
				polygons[y][x] = 0;

	for (int y = 1; y < width - 1; y++)
		for (int x = 1; x < length - 1; x++)
			if (polygons[y][x] == 0 && random(0, 10) <= 1)
				plantTree(x, y);

	draw();
	system("pause");
	system("cls");

	for (int y = 1; y < width - 1; y++)
		for (int x = 1; x < length - 1; x++)
			if (polygons[y][x] == -8 && polygons[y - 1][x] >= -7 && polygons[y][x - 1] >= -7 && polygons[y][x + 1] >= -7 && polygons[y + 1][x] >= -7)
				polygons[y][x] = 0;
}

std::string World::paint(int high)
{
	std::string res;

	switch (high)
	{
	case -11:
	case -10:
	case -9:
		res = "\x1b[34m";
		break;
	case -8:
		res = "\x1b[94m";
		break;
	case -7:
	case -6:
	case -5:
	case -4:
	case -3:
	case -2:
	case -1:
	case 0:
		res = "\x1b[92m";
		break;
	case 1:
		res = "\x1b[32m";
	}

	res += tile;
	res += "\x1b[0m";
	return res;
}

void World::draw()
{
	for (int y = 1; y < width - 1; y++)
	{
		for (int x = 1; x < length - 1; x++)
			std::cout << paint(polygons[y][x]);// << ' ' << vertexes[y][x];
		std::cout << '\n';
	}
}

void World::clean()
{
	std::cout << "\x1b[2J";
}