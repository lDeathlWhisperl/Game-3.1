#pragma once

#include <windows.h>

#include "HUD.h"
#include "World.h"
#include "Dungeon.h"


class Render
{
	static std::string paint(double);
public:
	static void draw_world(World&, Player&);

	static void draw_dungeon(Dungeon&, Player&);

	static void update();
};