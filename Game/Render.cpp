#include "Render.h"

//32 - tree
//92 - field

//34 - deep water
//94 - bright water
//36 - river

//93 - sand
//90 - stone
//33 - chest

std::string Render::paint_world(double high)
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

std::string Render::paint_dungeon(int num)
{
	unsigned char tile = 219;
	std::string res;
	switch (num)
	{
	case 1:
		res = "\x1b[96m";
		break;
	case 2:
		res = "\x1b[90m";
		break;
	case 3:
		res = "\x1b[33m";
		break;
	default:
		res = "\x1b[30m";
	}
	res += tile;
	res += "\x1b[0m";
	return res;
}

 
void Render::draw_dungeon(Dungeon dungeon, Player& player)
{
	HUD hud;

	for (int y = 0; y < dungeon.getHeight(); y++)
	{
		for (int x = 0; x < dungeon.getWidth(); x++)
		{
			bool player_coords = (x == player.getPos_x() && y == player.getPos_y());
			hud.addToViewport(player, x, y, 1, 1);

			if (player_coords)
				std::cout << player.showPlayer();
			else
				std::cout << paint_dungeon(dungeon.get(x, y));
		}
		std::cout << '\n';
	}
}

void Render::draw_world(World &world, Player &player)
{
	HUD hud;
	bool do_once = true;

	for (int y = 1; y < world.getWidth()-8; y++)
	{
		for (int x = 1; x < world.getLength()-16; x++)
		{
			bool player_coords = x == (world.getLength()-15) / 2 && y == (world.getWidth()-7) / 2;
			hud.addToViewport(player, x, y, 2, 2);

			//
			if (player_coords && player.getLastPressedKey() == 32 && world.getMap(x, y) == 776)
			{
				system("cls");
				world.enterTheDungeon(player);
				system("cls");
			}
			//

			player.breakBase(x, y, player_coords);

			if (player.placeBase(x, y, player_coords, do_once))
				continue;

			if (player_coords && world.getMap(x, y) == 4)
				player.getDamage(1);

			if (player_coords && world.getMap(x, y) != 2)
				std::cout << player.showPlayer();
			else
				std::cout << paint_world(world.getMap(x, y));
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