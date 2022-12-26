#pragma once

#include <windows.h>

#include "HUD.h"
#include "World.h"
#include "Dungeon.h"


class Render
{
	static std::string paint(double);

	Render() {};
public:
	static void draw_world(World&, Player&);

	static void draw_castle_dungeon(Dungeon&, Player&);

	static void draw_pyramid_dungeon(Dungeon&, Player&);

	static void update();
};