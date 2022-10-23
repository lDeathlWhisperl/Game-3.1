#pragma once

#include "World.h"
#include "Player.h"
#include "HUD.h"
#include "Block.h"

#include <iostream>
#include <windows.h>

class Render
{
	std::string paint(double);
public:
	void draw(World&, Player&, std::vector<Block>&);

	void update();
};