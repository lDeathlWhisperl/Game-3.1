#include "Pyramid.h"

int Pyramid::pos_y = 0, 
    Pyramid::pos_x = 0,
    Pyramid::brick = 5, 
    Pyramid::door = 6;

double** Pyramid::world_copy;

void Pyramid::line(int x, int y)
{
	pos_x -= 14;
	if (pos_x < 0) pos_x = 0;

	for (int i = pos_x; i <= x; i++)
		world_copy[y][i] = brick;

	if (x - 7 >= 0)
		world_copy[y][x - 7] = door;
}

void Pyramid::line(int& x)
{
	pos_y--;
	pos_x++;
	x--;
	if (pos_y < 0) pos_y = 0;
	if (x < 0) x = 0;

	for (int i = pos_x; i <= x; i++)
		world_copy[pos_y][i] = brick;
}

bool Pyramid::isColapse()
{
	int temp_x = pos_x - 15,
		temp_y = pos_y - 7;

	if (temp_x < 0) temp_x = 0;
	if (temp_y < 0) temp_y = 0;

	for (int y = temp_y; y < pos_y; y++)
		for (int x = temp_x; x < pos_x; x++)
			if (world_copy[y][x] == brick)
				return true;

	return false;
}

void Pyramid::draw(double** world, int x, int y)
{
	pos_x = x;
	pos_y = y;

	world_copy = world;
	if (isColapse()) return;
	//
	line(x, y);
	if (pos_y == 0) return;
	//
	line(x);
	if (pos_y == 0) return;
	//
	line(x);
	if (pos_y == 0) return;
	//
	line(x);
	if (pos_y == 0) return;
	//
	line(x);
	if (pos_y == 0) return;
	//
	line(x);
	if (pos_y == 0) return;
	//
	line(x);
	if (pos_y == 0) return;
	//
	line(x);
}