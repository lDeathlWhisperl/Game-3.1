#include "World.h"

//32 - tree
//92 - field

//34 - deep water
//94 - bright water
//36 - river

//93 - sand
//90 - stone
//33 - chest

void World::plantTree(int getLength, int getWidth)
{
	map[getWidth - 1][getLength] = 2;
	map[getWidth][getLength - 1] = 2;
	map[getWidth][getLength] = 2;
}

void World::plantCactus(int getLength, int getWidth)
{
	if (!(map[getWidth - 1][getLength - 1] > 0.5 && map[getWidth - 1][getLength - 1] <= 0.545))
		map[getWidth - 1][getLength - 1] = 3;
	if (!(map[getWidth - 1][getLength] > 0.5 && map[getWidth - 1][getLength] <= 0.545))
		map[getWidth - 1][getLength] = 3;
	if (!(map[getWidth - 1][getLength + 1] > 0.5 && map[getWidth - 1][getLength + 1] <= 0.545))
		map[getWidth - 1][getLength + 1] = 3;
	if (!(map[getWidth][getLength - 1] > 0.5 && map[getWidth][getLength - 1] <= 0.545))
		map[getWidth][getLength - 1] = 3;

	map[getWidth][getLength] = 4;

	if (!(map[getWidth][getLength + 1] > 0.5 && map[getWidth][getLength + 1] <= 0.545))
		map[getWidth][getLength + 1] = 3;
	if (!(map[getWidth + 1][getLength - 1] > 0.5 && map[getWidth + 1][getLength - 1] <= 0.545))
		map[getWidth + 1][getLength - 1] = 3;
	if (!(map[getWidth + 1][getLength] > 0.5 && map[getWidth + 1][getLength] <= 0.545))
		map[getWidth + 1][getLength] = 3;
	if (!(map[getWidth + 1][getLength + 1] > 0.5 && map[getWidth + 1][getLength + 1] <= 0.545))
		map[getWidth + 1][getLength + 1] = 3;
}

void World::landscape()
{
	for (int getWidth = 0; getWidth < width; getWidth++)
	{
		map[getWidth] = new double[length];
		for (int getLength = 0; getLength < length; getLength++)
			map[getWidth][getLength] = 0;
	}
}

void World::generator(unsigned int seed, int x_index, int y_index)
{
	PerlinNoise pn(seed);
	landscape();

	for (int getWidth = 0; getWidth < width; getWidth++)
		for (int getLength = 0; getLength < length; getLength++)
		{
			double t_x = (double)(getLength + x_index) / ((double)length);
			double t_y = (double)(getWidth + y_index) / ((double)width);

			//landscape noise
			map[getWidth][getLength] = pn.noise(3 * t_x, 3 * t_y, 600);

			//Desert
			if (pn.noise(-0.8 * t_x, -0.8 * t_y, 90000) * 10 < 4.5)
				if (!(map[getWidth][getLength] > 0.5 && map[getWidth][getLength] <= 0.545))
					map[getWidth][getLength] = 3;

			//foliage noise
			if ((map[getWidth][getLength] > 0.34 && map[getWidth][getLength] <= 0.5 || map[getWidth][getLength] >= 0.546) && map[getWidth][getLength] < 1 && getWidth > 0 && getLength > 0)
				if (pn.noise(222 * t_x, 222 * t_y, 600) >= 0.38 && pn.noise(222 * t_x, 222 * t_y, 600) <= 0.45)
					plantTree(getLength, getWidth);

			if (map[getWidth][getLength] == 3 && getLength > 0 && getLength < length - 1 && getWidth > 0 && getWidth < width - 1)
				if (pn.noise(555 * t_x, 555 * t_y, 600) >= 0.38 && pn.noise(555 * t_x, 555 * t_y, 600) <= 0.45)
					plantCactus(getLength, getWidth);
		}
}

double World::getMap(int getLength, int getWidth)
{
	return map[getWidth][getLength];
}

int World::getLength()
{
	return length;
}

int World::getWidth()
{
	return width;
}