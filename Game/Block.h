#pragma once

#include "Actor.h"

#include <iostream>

class Block : public Actor
{
public:
	Block(int x, int y);

	void offset(char pressedKey);

	void show();
};