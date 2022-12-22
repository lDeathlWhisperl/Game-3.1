#pragma once

#include "Player.h"

class Castle final
{
	static int door, stone, window, pos_x, pos_y;

	static double** world_copy;

	static void line(int x, int y);

	static void line_2(int x);

	static void line_3(int x);

	static void line_4(int x);

	static void line_5(int& x);

	static void line_6(int x);

	static void line_7(int x);

	static bool isColapse();
public:
	static void draw(double** world, int x, int y);

	static void enter(Player&, int, int);
};