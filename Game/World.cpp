#include "World.h"

World::~World()
{
	for (int i = 0; i < width; i++)
		delete[] map[i];
	delete[] map;
}

void World::plantTree(int x, int y)
{
	if (map[y - 1][x] != 776)map[y - 1][x] = 2;
	map[y][x - 1] = 2;
	map[y][x] = 2;
}

void World::plantCactus(int x, int y)
{
	if (!(map[y - 1][x - 1] > 0.5 && map[y - 1][x - 1] <= 0.545))
		map[y - 1][x - 1] = 3;
	if (!(map[y - 1][x] > 0.5 && map[y - 1][x] <= 0.545))
		map[y - 1][x] = 3;
	if (!(map[y - 1][x + 1] > 0.5 && map[y - 1][x + 1] <= 0.545))
		map[y - 1][x + 1] = 3;
	if (!(map[y][x - 1] > 0.5 && map[y][x - 1] <= 0.545))
		map[y][x - 1] = 3;

	map[y][x] = 4;

	if (!(map[y][x + 1] > 0.5 && map[y][x + 1] <= 0.545))
		map[y][x + 1] = 3;
	if (!(map[y + 1][x - 1] > 0.5 && map[y + 1][x - 1] <= 0.545))
		map[y + 1][x - 1] = 3;
	if (!(map[y + 1][x] > 0.5 && map[y + 1][x] <= 0.545))
		map[y + 1][x] = 3;
	if (!(map[y + 1][x + 1] > 0.5 && map[y + 1][x + 1] <= 0.545))
		map[y + 1][x + 1] = 3;
}

void World::landscape()
{
	for (int y = 0; y < width; y++)
	{
		map[y] = new double[length];
		for (int x = 0; x < length; x++)
			map[y][x] = 0;
	}
}

void World::generator(unsigned int seed, int x_index, int y_index)
{
	PerlinNoise pn(seed);

	for (int y = 0; y < width; y++)
		for (int x = 0; x < length; x++)
		{
			double t_x = (double)(x + x_index) / ((double)length);
			double t_y = (double)(y + y_index) / ((double)width);

			//landscape noise
			map[y][x] = pn.noise(3 * t_x, 3 * t_y, 600);

			//Desert
			if (pn.noise(-0.8 * t_x, -0.8 * t_y, 90000) * 10 < 4.5)
				if (!(map[y][x] > 0.5 && map[y][x] <= 0.545))
					map[y][x] = 3;

			//foliage noise
			if ((map[y][x] > 0.34 && map[y][x] <= 0.5 || map[y][x] >= 0.546) && map[y][x] < 1 && y > 0 && x > 0)
				if (pn.noise(222 * t_x, 222 * t_y, 600) >= 0.38 && pn.noise(222 * t_x, 222 * t_y, 600) <= 0.45)
					plantTree(x, y);

			if (map[y][x] == 3 && x > 0 && x < length - 1 && y > 0 && y < width - 1)
				if (pn.noise(555 * t_x, 555 * t_y, 600) >= 0.38 && pn.noise(555 * t_x, 555 * t_y, 600) <= 0.45)
					plantCactus(x, y);

			//spawn castle
			if ((map[y][x] > 0.3 && map[y][x] != 3 && map[y][x] != 4) && (map[y][x] < 0.5 || map[y][x] > 0.545))
				if (pn.noise(666 * t_x, 666 * t_y, 600) * 10 <= 1.3)
					castle.draw(map, x, y);
		}
}

double World::getMap(int x, int y)
{
	return map[y][x];
}

int World::getLength()
{
	return length;
}

int World::getWidth()
{
	return width;
}

void World::enterTheDungeon(Player& player)
{
	Dungeon dungeon(length - 17, width - 8);
	dungeon.generate(5);

	int temp_x = player.getPos_x(),
		temp_y = player.getPos_y();

	player.setPos_x(dungeon.getStart_x());
	player.setPos_y(dungeon.getStart_y());

	while (true)
	{
		Render::draw_dungeon(dungeon, player);

		int top = dungeon.get(player.getPos_x(), player.getPos_y() - 1),
			left = dungeon.get(player.getPos_x() - 1, player.getPos_y()),
			right = dungeon.get(player.getPos_x() + 1, player.getPos_y()),
			bottom = dungeon.get(player.getPos_x(), player.getPos_y() + 1);

		player.collision(top, left, right, bottom);
		player.controller();

		if (!player.getStatus() || dungeon.isExit())
			break;

		Render::update();
	}

	player.setPos_x(temp_x);
	player.setPos_y(temp_y);
}