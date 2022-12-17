#pragma once

#include <iostream>

#include "Character.h"

class HUD
{
	int length = 0, pos_x, pos_y;

	void frame();

	void healthBar(Character*);

	void armorBar(Character*);

public:
	HUD(int);

	int getLength();

	int getWidth()
	{
		return pos_y + 4;
	}

	int getPos_x()
	{
		return pos_x;
	}

	int getPos_y()
	{
		return pos_y;
	}

	void addToViewport(Character*);
};