#include "castle.h"
#include "Logging.h"
#include "Render.h"


int Castle::door   = 5,
	Castle::stone  = 3,
	Castle::window = 6,
	Castle::pos_x  = 0, 
	Castle::pos_y  = 0;

double** Castle::world_copy;

void Castle::line(int x, int y)
{
	pos_x -= 14;
	if (pos_x < 0) pos_x = 0;

	for (int i = pos_x; i <= x; i++)
		world_copy[y][i] = stone;

	if (x - 7 >= 0)
		world_copy[y][x - 7] = door;
}

void Castle::line_2(int x)
{
	pos_y--;
	if (pos_y < 0) pos_y = 0;

	for (int i = x, count = 3; i >= pos_x; i--, count++)
		if (count % 4 == 0)
			world_copy[pos_y][i] = window;
		else
			world_copy[pos_y][i] = stone;
}

void Castle::line_3(int x)
{
	pos_y--;
	if (pos_y < 0) pos_y = 0;

	for (int i = pos_x; i <= x; i++)
		world_copy[pos_y][i] = stone;
}

void Castle::line_4(int x)
{
	pos_y--;
	if (pos_y < 0) pos_y = 0;

	for (int i = x, count = 1; i >= pos_x; count++, i--)
		if ((count % 2 != 0) || (count >= 6 && count <= 10))
			world_copy[pos_y][i] = stone;
}

void Castle::line_5(int& x)
{
	pos_y--;
	if (pos_y < 0) pos_y = 0;
	x -= 4;
	if (x < 0) x = 0;

	for (int i = x, count = 5; count < 12; count++, i--)
		if (count == 6 || count == 10)
			world_copy[pos_y][i] = window;
		else
			world_copy[pos_y][i] = stone;
}

void Castle::line_6(int x)
{
	pos_y--;
	if (pos_y < 0) pos_y = 0;

	for (int i = x, count = 5; count < 12; count++, i--)
		world_copy[pos_y][i] = stone;
}

void Castle::line_7(int x)
{
	pos_y--;
	if (pos_y < 0) pos_y = 0;

	for (int i = x, count = 5; count < 12; count++, i--)
		if (count % 2 != 0)
			world_copy[pos_y][i] = stone;
}

bool Castle::isColapse()
{
	int temp_x = pos_x - 15,
		temp_y = pos_y - 7;

	if (temp_x < 0) temp_x = 0;
	if (temp_y < 0) temp_y = 0;

	for (int y = temp_y; y < pos_y; y++)
		for (int x = temp_x; x < pos_x; x++)
			if (world_copy[y][x] == 3)
				return true;

	return false;
}

void Castle::draw(double** world, int x, int y)
{
	pos_x = x;
	pos_y = y;

	world_copy = world;
	if (isColapse()) return;
	//
	line(x, y);
	if (pos_y == 0) return;
	//
	line_2(x);
	if (pos_y == 0) return;
	//
	line_3(x);
	if (pos_y == 0) return;
	//
	line_4(x);
	if (pos_y == 0) return;
	//
	line_5(x);
	if (pos_y == 0) return;
	//
	line_6(x);
	if (pos_y == 0) return;
	//
	line_7(x);
}

void Castle::enter(Player& player, int length, int width)
{
	srand(player.getPos_x() + player.getPos_y());
	debug::log->request("Dungeon generation seed: " + std::to_string(player.getPos_x() + player.getPos_y()) + "\n\n");

	Dungeon dungeon(length, width);
	dungeon.generate(5);

	int temp_x = player.getPos_x(),
		temp_y = player.getPos_y();

	player.setPos_x(dungeon.spawn_x());
	player.setPos_y(dungeon.spawn_y());

	while (!dungeon.isExit() && player.getStatus())
	{
		Render::draw_dungeon(dungeon, player);

		int top    = dungeon.get(player.getPos_x(), player.getPos_y() - 1),
			left   = dungeon.get(player.getPos_x() - 1, player.getPos_y()),
			right  = dungeon.get(player.getPos_x() + 1, player.getPos_y()),
			bottom = dungeon.get(player.getPos_x(), player.getPos_y() + 1);

		player.controller(top, left, right, bottom);

		//for (AI* monster : dungeon.monsters) monster->controller(player);

		Render::update();
	}

	player.setPos_x(temp_x);
	player.setPos_y(temp_y);
}