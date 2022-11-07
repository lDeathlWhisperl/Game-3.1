#include "Render.h"

//32 - tree
//92 - field

//34 - deep water
//94 - bright water
//36 - river

//93 - sand
//90 - stone
//33 - chest

std::string Render::paint(double high)
{
	std::string res;
	unsigned char tile = 219;

	if (high <= 0.2)
		res = "\x1b[34m";				//deep water
	else if (high > 0.2 && high <= 0.3)
		res = "\x1b[94m";				//bright water
	else if (high > 0.3 && high <= 0.34)
		res = "\x1b[93m";				//sand
	else if (high > 0.5 && high <= 0.545)
		res = "\x1b[36m";				//river
	else if (high == 777)
		res = "\x1b[90m";
	else if(high == 776)
		res = "\x1b[33m";
	else if(high == 775)
		res = "\x1b[30m";
	else
		res = "\x1b[92m";               //field

	if (high == 2 || high == 4)
		res = "\x1b[32m";				//tree or cactus

	if (high == 3)
		res += "\x1b[93m";				//desert

	res += tile;
	res += "\x1b[0m";
	return res;
}

void Render::draw(World &world, Player &player)
{
	HUD hud;
	bool do_once = true;

	for (int y = 0; y < world.getWidth(); y++)
	{
		for (int x = 0; x < world.getLength(); x++)
		{
			bool player_coords = x == world.getLength() / 2 && y == world.getWidth() / 2;
			hud.addToViewport(player, x, y);

			player.breakBase(x, y, player_coords);

			if (player.placeBase(x, y, player_coords, do_once))
				continue;

			if (player_coords && world.getMap(x, y) == 4)
				player.getDamage(1);

			if (player_coords && world.getMap(x, y) != 2)
				std::cout << player.showPlayer();
			else
				std::cout << paint(world.getMap(x, y));
		}
		std::cout << '\n';
	}
}

void Render::update()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}