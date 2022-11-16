#pragma once

#include <windows.h>

#include "Player.h"
#include "HUD.h"
#include "World.h"
#include "Dungeon.h"


class Render
{
	static std::string paint_dungeon(int);

	static std::string paint_world(double);

	static void enterTheDungeon(Player&, int, int);
public:
	static void draw_world(World&, Player&);

	static void draw_dungeon(Dungeon&, Player&);

	static void update();
};