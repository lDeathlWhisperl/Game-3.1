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
		res = "\x1b[33m";				//door and pyramid brick
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

void Render::enterTheDungeon(Player& player, int length, int width)
{
	srand(player.getPos_x() + player.getPos_y());
	Dungeon dungeon(length, width);
	dungeon.generate(5);

	std::ofstream fout("log.txt", std::ios::app);
	fout << "Seed генерации подземелья: " << player.getPos_x() + player.getPos_y() << "\n\n";
	fout.close();

	int temp_x = player.getPos_x(),
		temp_y = player.getPos_y();

	player.setPos_x(dungeon.spawn_x());
	player.setPos_y(dungeon.spawn_y());

	while (true)
	{
		Render::draw_dungeon(dungeon, player);

		int top = dungeon.get(player.getPos_x(), player.getPos_y() - 1),
			left = dungeon.get(player.getPos_x() - 1, player.getPos_y()),
			right = dungeon.get(player.getPos_x() + 1, player.getPos_y()),
			bottom = dungeon.get(player.getPos_x(), player.getPos_y() + 1);

		player.controller(top, left, right, bottom);

		if (dungeon.isExit()) break;
		if (!player.getStatus()) exit(0);

		for (AI* monster : dungeon.monsters) monster->controller(player);

		Render::update();
	}

	player.setPos_x(temp_x);
	player.setPos_y(temp_y);
}

 
void Render::draw_dungeon(Dungeon& dungeon, Player& player)
{
	HUD hud;
	
	for (int y = 0; y < dungeon.getHeight(); y++)
	{
		for (int x = 0; x < dungeon.getWidth(); x++)
		{
			bool player_coords = (x == player.getPos_x() && y == player.getPos_y());
			bool skip = false;
			hud.addToViewport(&player, x, y, 1, 1);

			if (player_coords && dungeon.get(x, y) == 5 && player.getLastPressedKey() == 32)
				dungeon.Exit();
			
			for (AI* monster : dungeon.monsters)
				if (monster->getPos_x() == x && monster->getPos_y() == y)
				{
					monster->draw();
					skip = true;
					break;
				}
			
			if (player_coords && !skip)
				std::cout << player.showPlayer();
			else if (!skip)
				std::cout << paint(dungeon.get(x, y));
		}
		std::cout << '\n';
	}
}

void Render::draw_world(World &world, Player &player)
{
	HUD hud;
	bool do_once = true;

	for (int y = 1; y < world.getWidth(); y++)
	{
		for (int x = 1; x < world.getLength(); x++)
		{
			bool player_coords = x == (world.getLength()) / 2 && y == (world.getWidth()) / 2;
			hud.addToViewport(&player, x, y, 2, 2);

			if (player_coords && player.getLastPressedKey() == 32 && world.getMap(x, y) == 5)
			{
				system("cls");
				//world.clear();
				enterTheDungeon(player, world.getLength(), world.getWidth());
				//world.landscape();
				system("cls");
				return;
			}

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