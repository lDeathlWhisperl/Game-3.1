#include "World.h"
#include <fstream>

World::World(int l, int w) : length(l), width(w)
{
	std::ofstream fout("log.txt", std::ios::app);
	fout << "Создание мира...\n\n";
	fout.close();
}

World::~World()
{
	std::ofstream fout("log.txt", std::ios::app);
	fout << "Удаление мира...\n\n";
	fout.close();
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
		map[y - 1][x - 1] = 0.34;
	if (!(map[y - 1][x] > 0.5 && map[y - 1][x] <= 0.545))
		map[y - 1][x] = 0.34;
	if (!(map[y - 1][x + 1] > 0.5 && map[y - 1][x + 1] <= 0.545))
		map[y - 1][x + 1] = 0.34;
	if (!(map[y][x - 1] > 0.5 && map[y][x - 1] <= 0.545))
		map[y][x - 1] = 0.34;

	map[y][x] = 4;

	if (!(map[y][x + 1] > 0.5 && map[y][x + 1] <= 0.545))
		map[y][x + 1] = 0.34;
	if (!(map[y + 1][x - 1] > 0.5 && map[y + 1][x - 1] <= 0.545))
		map[y + 1][x - 1] = 0.34;
	if (!(map[y + 1][x] > 0.5 && map[y + 1][x] <= 0.545))
		map[y + 1][x] = 0.34;
	if (!(map[y + 1][x + 1] > 0.5 && map[y + 1][x + 1] <= 0.545))
		map[y + 1][x + 1] = 0.34;
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
					map[y][x] = 0.34;
			
			//foliage noise
			if ((map[y][x] > 0.34 && map[y][x] <= 0.5 || map[y][x] >= 0.546) && map[y][x] < 1 && y > 0 && x > 0)
				if (pn.noise(222 * t_x, 222 * t_y, 600) >= 0.38 && pn.noise(222 * t_x, 222 * t_y, 600) <= 0.45)
					plantTree(x, y);

			if (map[y][x] == 0.34 && x > 0 && x < length - 1 && y > 0 && y < width - 1)
				if (pn.noise(555 * t_x, 555 * t_y, 600) >= 0.38 && pn.noise(555 * t_x, 555 * t_y, 600) <= 0.45)
					plantCactus(x, y);

			//spawn castle
			if ((map[y][x] > 0.34 && map[y][x] != 4) && (map[y][x] < 0.5 || map[y][x] > 0.545))
				if (pn.noise(666 * t_x, 666 * t_y, 600) <= 0.13)
					castle.draw(map, x, y);
		}
}

double World::getMap(int x, int y)
{
	return map[y][x];
}

int World::getLength()
{
	return length - 16;
}

int World::getWidth()
{
	return width - 8;
}

void World::clear()
{
	for (int i = 0; i < width; i++)
		delete[] map[i];
}