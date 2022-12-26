#pragma once

#include "Player.h"

class Pyramid final
{
	static int pos_y, pos_x;
	static int brick, door;
	static double **world_copy;

	static void line(int, int);

	static void line(int&);

	static bool isColapse();
public:
	static void draw(double**, int, int);

	static void enter(Player&, int, int);
};