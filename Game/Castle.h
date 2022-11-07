#pragma once

class Castle
{
public:
	void draw(double **world, int x, int y)
	{
		int t_x = x,
			t_y = y;

		x -= 15;
		if (x < 0) x = 0;

		for (int i = x; i < t_x; i++)
			world[y][i] = 777;

		y--;
		if (y < 0) y = 0;

		for (int i = x, count = 1; i < t_x; i++, count++)
			if (count == 2 || count == 6 || count == 10 || count == 14)
				world[y][i] = 775;
			else
				world[y][i] = 777;

		if (t_x - 8 >= 0)
			world[t_y][t_x - 8] = 776;

	}
};