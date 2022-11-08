#pragma once

class Castle
{
	int door = 776,
		stone = 777,
		window = 775;

	int pos_x = 0, 
		pos_y = 0;

	void line_1(double **world, int &x, int &y)
	{
		pos_x -= 14;
		if (pos_x < 0) pos_x = 0;

		for (int i = pos_x; i <= x; i++)
			world[y][i] = stone;

		if (x - 7 >= 0)
			world[y][x - 7] = door;
	}

	void line_2(double **world, int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = x, count = 3; i >= pos_x; i--, count++)
			if (count % 4 == 0)
				world[pos_y][i] = window;
			else
				world[pos_y][i] = stone;
	}

	void line_3(double **world, int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = pos_x; i <= x; i++)
			world[pos_y][i] = stone;
	}

	void line_4(double **world, int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = x, count = 1; i >= pos_x; count++, i--)
			if (((count % 2 != 0 && count < 5) || (count % 2 != 0 && count > 11)) || (count > 4 && count < 12))
				world[pos_y][i] = stone;

	}

	void line_5(double **world, int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = x, count = 1; i >= pos_x; count++, i--)
			if (count == 12)
				break;
			else if (count == 6 || count == 10)
				world[pos_y][i] = window;
			else if (count > 4)
				world[pos_y][i] = stone;
	}

	void line_6(double **world, int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = x, count = 1; i >= pos_x; count++, i--)
			if (count > 4 && count < 12)
				world[pos_y][i] = stone;
	}

	void line_7(double **world, int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = x, count = 1; i >= pos_x; count++, i--)
			if (count > 4 && count < 12 && count % 2 != 0)
				world[pos_y][i] = stone;
	}
public:
	void draw(double** world, int x, int y)
	{
		pos_x = x;
		pos_y = y;

		//
		line_1(world, x, y);
		if (pos_y == 0) return;
		//
		line_2(world, x);
		if (pos_y == 0) return;
		//
		line_3(world, x);
		if (pos_y == 0) return;
		//
		line_4(world, x);
		if (pos_y == 0) return;
		//
		line_5(world, x);
		if (pos_y == 0) return;
		//
		line_6(world, x);
		if (pos_y == 0) return;
		//
		line_7(world, x);
	}
};