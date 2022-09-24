#include <iostream>
#include <cmath>
#include <vector>
#include "World.h"

//32 - лес
//92 - поляна

//34 - темная вода
//94 - светлая вода
//36 - ручей

//93 - песок
//90 - камень
//33 - мост

void World::dimond(int sq_a, int sq_b, int sq_c, int sq_d, int length)
{
	int landscapeSize = vertexes.size() - 1;

	int A = sq_a,
		B = sq_b,
		C = sq_c,
		D = sq_d;

	int mid = length / 2;

	vertexes[mid][mid] = 1;

	int left = 0, 
		top = mid,
		right = length - 1, 
		bottom = mid;

	vertexes[mid][left] = 1;
	vertexes[0][top] = 1;
	vertexes[mid][right] = 1;
	vertexes[landscapeSize][bottom] = 1;

	/*!!!*/
}

void World::landscape(int length, int width)
{
	for (int y = 0; y < width; y++)
	{
		vertexes.push_back(std::vector<int>());
		for (int x = 0; x < length; x++)
			vertexes[y].push_back(0);
	}
}

void World::generator(int length, int width)
{
	landscape(length, width);

	int landscapeSize = vertexes.size() - 1;

	int sq_a = 0,
		sq_b = length - 1,
		sq_c = 0, 
		sq_d = length - 1;

	vertexes[0][sq_a] = 1;
	vertexes[0][sq_b] = 1;
	vertexes[landscapeSize][sq_c] = 1;
	vertexes[landscapeSize][sq_d] = 1;

	dimond(sq_a, sq_b, sq_c, sq_d, length);
}

std::string World::paint(int high)
{
	std::string res;

	if (high == 1)
		res = "\x1b[31m";

	res += tile;
	res += "\x1b[0m";
	return res;
}

void World::draw(int length, int width)
{
	generator(length, width);

	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < length; x++)
		{
			std::cout << paint(vertexes[y][x]);
		}
		std::cout << '\n';
	}

}

void World::clean()
{
	std::cout << "\x1b[2J";
}