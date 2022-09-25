#include <iostream>
#include <cmath>
#include "World.h"

//32 - forest
//92 - field

//34 - deep water
//94 - bright water
//36 - river

//93 - sand
//90 - stone
//33 - bridge

int random(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void World::landscape()
{
	for (size_t y = 0; y < width; y++)
	{
		std::vector<int> temp;
		for (size_t x = 0; x < length; x++)
			temp.push_back(random(0, 10));
		vertexes.push_back(temp);
	}
}

void World::smooth()
{
	for (int y = 1; y < width-1; y++)
	{
		for (int x = 1; x < length-1; x++)
		{
			int vertex_count = 1;
			int vertex_sum = vertexes[y][x];
			
			vertexes[y][x] = (vertexes[y-1][x-1]+ vertexes[y-1][x] + vertexes[y-1][x+1]+ vertexes[y][x-1]+ vertexes[y][x]+ vertexes[y][x+1]+ vertexes[y+1][x-1]+ vertexes[y+1][x]+ vertexes[y+1][x+1]) / 9;
		}
	}
} 

void World::generator()
{
	srand(static_cast<unsigned int>(time(0)));
	landscape();

	smooth();

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
			if (random(1, 10) <= 1)
				vertexes[y][x] = random(3, 5);

	smooth();

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
			if (random(1, 10) <= 3)
				vertexes[y][x] = random(3, 7);

	smooth();
}

std::string World::paint(int high)
{
	std::string res;
	
	switch (high)
	{
	case 1:
		res = "\x1b[34m"; // deep water
		break;
	case 2:
		res = "\x1b[94m"; // water
		break;
	case 3:
		res = "\x1b[92m"; // field
		break;
	default:
		res = "\x1b[32m"; // trees
	}

	res += tile;
	res += "\x1b[0m";
	return res;
}

void World::draw()
{
	for (int y = 2; y < width-2; y++)
	{
		for (int x = 2; x < length-2; x++)
			std::cout << paint(vertexes[y][x]);// << ' ';
		std::cout << '\n';
	}
		
}

void World::clean()
{
	std::cout << "\x1b[2J";
}