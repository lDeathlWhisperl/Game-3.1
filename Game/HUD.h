#pragma once

#include <iostream>

#include "Character.h"

class HUD
{
	int length = 0;

	void frame();

	void healthBar(Character);

	void armorBar(Character);

public:

	int getLength();

	void addToViewport(Character, int&, int&, int, int);
};