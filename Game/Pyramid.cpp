#include <string>

#include "Pyramid.h"
#include "Dungeon.h"
#include "Render.h"
#include "Logging.h"

int Pyramid::pos_y = 0, 
    Pyramid::pos_x = 0,
    Pyramid::brick = 10, 
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

void Pyramid::enter(Player &player, int length, int width)
{
	srand(player.getPos_x() + player.getPos_y());
	debug::log->request("Dungeon generation seed: " + std::to_string(player.getPos_x() + player.getPos_y()) + "\n\n");

	Dungeon dungeon(length, width);
	dungeon.generate(5, { 1, 3 }, {3, 3});

	int temp_x = player.getPos_x(),
		temp_y = player.getPos_y();

	player.setPos_x(dungeon.spawn_x());
	player.setPos_y(dungeon.spawn_y());

	while (!dungeon.isExit() && player.getStatus())
	{
		Render::draw_pyramid_dungeon(dungeon, player);

		int top = dungeon.getVertex(player.getPos_x(), player.getPos_y() - 1),
			left = dungeon.getVertex(player.getPos_x() - 1, player.getPos_y()),
			right = dungeon.getVertex(player.getPos_x() + 1, player.getPos_y()),
			bottom = dungeon.getVertex(player.getPos_x(), player.getPos_y() + 1);

		player.controller(top, left, right, bottom);

		//for (AI* monster : dungeon.monsters) monster->controller(player);

		Render::update();
	}

	player.setPos_x(temp_x);
	player.setPos_y(temp_y);
}