#pragma once

class Castle
{
public:
	void draw(double** world, int x, int y)
	{
		int t_x = x,
			t_y = y;

		int door = 776,
			stone = 777,
			window = 775;
		//
		x -= 14;
		if (x < 0) x = 0;

		for (int i = x; i <= t_x; i++)
			world[y][i] = stone;

		if (t_x - 7 >= 0)
			world[t_y][t_x - 7] = door;

		if (y == 0) return;
		//
		y--;
		if (y < 0) y = 0;

		for (int i = t_x, count = 3; i >= x; i--, count++)
			if (count % 4 == 0)
				world[y][i] = window;
			else
				world[y][i] = stone;

		if (y == 0) return;
		//
		y--;
		if (y < 0) y = 0;

		for (int i = x; i <= t_x; i++)
			world[y][i] = stone;

		if (y == 0) return;
		//
		y--;
		if (y < 0) y = 0;

		for (int i = t_x, count = 1; i >= x; count++, i--)
			if (((count % 2 != 0 && count < 5) || (count % 2 != 0 && count > 11)) || (count > 4 && count < 12))
				world[y][i] = stone;

		if (y == 0) return;
		//
		y--;
		if (y < 0) y = 0;

		for (int i = t_x, count = 1; i >= x; count++, i--)
			if (count == 12)
				break;
			else if (count == 6 || count == 10)
				world[y][i] = window;
			else if (count > 4)
				world[y][i] = stone;

		if (y == 0) return;
		//
		y--;
		if (y < 0) y = 0;

		for (int i = t_x, count = 1; i >= x; count++, i--)
			if (count > 4 && count < 12)
				world[y][i] = stone;

		if (y == 0) return;
		//
		y--;
		if (y < 0) y = 0;

		for (int i = t_x, count = 1; i >= x; count++, i--)
			if (count > 4 && count < 12 && count % 2 != 0)
				world[y][i] = stone;
	}
};