#include "Render.h"
#include "Castle.h"
#include "Logging.h"

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
	res.clear();
	unsigned char tile = 219;

	if (high <= 0.2)
		res = "\x1b[34m";				//deep water
	else if (high > 0.2 && high <= 0.3)
		res = "\x1b[94m";				//bright water
	else if (high > 0.3 && high <= 0.34)
		res = "\x1b[93m";				//sand and dessert
	else if (high > 0.5 && high <= 0.545)
		res = "\x1b[36m";				//river
	else
		res = "\x1b[92m";               //field

	int i = static_cast<int>(high);

	switch (i)
	{
	case 2:
	case 4:
		res = "\x1b[32m";				//tree and cactus
		break;
	case 3:
		res = "\x1b[90m";				//stone and dungeon walls
		break;
	case 5:
		res = "\x1b[33m";				//castle door and pyramid brick
		break;
	case 6:
		res = "\x1b[30m";				//window, dungeon void and pyramid passage
		break;
	case 7:
		res = "\x1b[96m";				//dungeon floor
		break;
	case 8:
		res = "\x1b[93m";				//pyramid floor
		break;
	}

	res += tile;
	res += "\x1b[0m";
	return res;
}
 
void Render::draw_dungeon(Dungeon& dungeon, Player& player)
{
	HUD hud(player.getMaxHP());
	int player_coords = dungeon.getVertex(player.getPos_x(), player.getPos_y());

	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int y = 0; y < dungeon.getHeight(); y++)
	{
		for (int x = 0; x < dungeon.getWidth()-1; x++)
		{
			bool p_coords = (x == player.getPos_x() && y == player.getPos_y());
			bool hud_coords = (x < hud.getPos_x() || x > hud.getLength()) || (y < hud.getPos_y() || y > hud.getWidth());

			if (p_coords && hud_coords)
				std::cout << player.showPlayer();
			else if (hud_coords)
				std::cout << paint(dungeon.getVertex(x, y));
			else
			{
				Position.X = x;
				Position.Y = y;
				SetConsoleCursorPosition(hOut, Position);
			}
		}
		std::cout << '\n';
	}

	hud.addToViewport(&player);
	
	if (player_coords == 5 && player.getLastPressedKey() == 32)
		dungeon.Exit();

	//for (int y = 0; y < dungeon.getHeight(); y++)
	//{
	//	for (int x = 0; x < dungeon.getWidth(); x++)
	//	{
	//		bool skip = false;
	//		
	//		for (AI* monster : dungeon.monsters)
	//			if (monster->getPos_x() == x && monster->getPos_y() == y)
	//			{
	//				monster->draw();
	//				skip = true;
	//				break;
	//			}
	//	}
	//	std::cout << '\n';
	//}
}

void Render::draw_world(World &world, Player &player)
{
	HUD hud(player.getMaxHP());
	bool do_once = true;
	int player_coords = static_cast<int>(world.getMap(world.getLength() / 2, world.getWidth() / 2));

	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	hud.addToViewport(&player);
	update();

	for (int y = 1; y < world.getWidth(); y++)
	{
		for (int x = 1; x < world.getLength(); x++)
		{
			bool p_coords = x == world.getLength() / 2 && y == world.getWidth() / 2;

			if (p_coords && world.getMap(x, y) != 2)
				std::cout << player.showPlayer();
			else if ((x <= hud.getPos_x() || x > hud.getLength()) || (y <= hud.getPos_y() || y > hud.getWidth()))
				std::cout << paint(world.getMap(x, y));
			else
			{
				Position.X = x;
				Position.Y = y - 1;
				SetConsoleCursorPosition(hOut, Position);
			}
		}
		std::cout << '\n';
	}

	if (player_coords == 4)
		player.getDamage(1);

	if (player.getLastPressedKey() == 32 && player_coords == 5)
	{
		system("cls");
		Castle::enter(player, world.getLength(), world.getWidth());
		system("cls");
		return;
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