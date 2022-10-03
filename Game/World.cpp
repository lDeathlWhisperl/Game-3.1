#include <iostream>
#include <cmath>
#include "Perlin.h"
#include "World.h"

//32 - tree
//92 - field

//34 - deep water
//94 - bright water

//93 - sand
//90 - stone
//33 - path

int random(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void World::plantTree(int x, int y)
{
	polygons[y - 1][x] = 2;
	polygons[y][x - 1] = 2;
	polygons[y][x] = 2;
	polygons[y][x + 1] = 2;
	polygons[y + 1][x] = 2;
}

void World::landscape()
{
	for (int y = 0; y < width; y++)
	{
		std::vector<double> temp;
		for (int x = 0; x < length; x++)
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

void World::generator(long long int seed)
{
	srand(static_cast<unsigned int>(time(0)));
	PerlinNoise pn(seed);
	landscape();

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
		{
			double t_x = (double)x / ((double)length);
			double t_y = (double)y / ((double)width);
			polygons[y][x] = pn.noise(3 * t_x, 3 * t_y, 600);
		}

	
	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
			if (polygons[y][x] > 0.34 && polygons[y][x] <= 0.5 || polygons[y][x] > 0.545)
				polygons[y][x] = 1;
	
	for (int y = 1; y < width-1; y++)
		for (int x = 1; x < length-1; x++)
			if (polygons[y][x] == 1 && random(0, 100) <= 5)
				plantTree(x, y);
	
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
		res = "\x1b[33m";				//paths
	else
		res = "\x1b[92m";

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
			std::cout << paint(polygons[y][x]);
		std::cout << '\n';
	}
}

void World::clean()
{
	std::cout << "\x1b[2J";
}