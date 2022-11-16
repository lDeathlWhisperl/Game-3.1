#pragma once

class Castle
{
	int door   = 776,
		stone  = 777,
		window = 775;

	int pos_x = 0, 
		pos_y = 0;

	double** world_copy = {};

	void line_1(int x, int y)
	{
		pos_x -= 14;
		if (pos_x < 0) pos_x = 0;

		for (int i = pos_x; i <= x; i++)
			world_copy[y][i] = stone;

		if (x - 7 >= 0)
			world_copy[y][x - 7] = door;
	}

	void line_2(int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = x, count = 3; i >= pos_x; i--, count++)
			if (count % 4 == 0)
				world_copy[pos_y][i] = window;
			else
				world_copy[pos_y][i] = stone;
	}

	void line_3(int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = pos_x; i <= x; i++)
			world_copy[pos_y][i] = stone;
	}

	void line_4(int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = x, count = 1; i >= pos_x; count++, i--)
			if ((count % 2 != 0) || (count >= 6 && count <= 10))
				world_copy[pos_y][i] = stone;
	}

	void line_5(int &x)
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

	void line_6(int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = x, count = 5; count < 12; count++, i--)
				world_copy[pos_y][i] = stone;
	}

	void line_7(int x)
	{
		pos_y--;
		if (pos_y < 0) pos_y = 0;

		for (int i = x, count = 5; count < 12; count++, i--)
			if (count % 2 != 0)
				world_copy[pos_y][i] = stone;
	}

	bool isColapse()
	{
		int temp_x = pos_x - 15,
			temp_y = pos_y - 7;

		if (temp_x < 0) temp_x = 0;
		if (temp_y < 0) temp_y = 0;

		for (int y = temp_y; y < pos_y; y++)
			for (int x = temp_x; x < pos_x; x++)
				if (world_copy[y][x] >= 775)
					return true;
				
		return false;
	}
public:
	void draw(double** world, int x, int y)
	{
		pos_x = x;
		pos_y = y;

		world_copy = world;
		if (isColapse()) return;
		//
		line_1(x, y);
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
};