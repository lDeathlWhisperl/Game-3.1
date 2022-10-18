#pragma once

#include <iostream>

#include "Player.h"

class HUD
{
	int length = 27;

	void frame();

	void healthBar(Player);

	void armorBar(Player);

public:

	int getLength();

	void draw(Player, int&, int&);
};