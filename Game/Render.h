#pragma once

#include "World.h"
#include "Player.h"
#include "HUD.h"

#include <iostream>
#include <windows.h>

class World;
class Dungeon;

class Render
{
	static std::string paint_dungeon(int);

	std::string paint_world(double);
public:
	void draw_world(World&, Player&);

	static void draw_dungeon(Dungeon, Player&);

	static void update();
};