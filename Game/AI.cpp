#include "AI.h"

AStar::Generator AI::generator;
int AI::count = 0;

AI::~AI()
{
	if (count == 1)
		generator.clearCollisions();
	count--;
	std::ofstream fout("log.txt", std::ios::app);
	fout << "Бот " << id << " уничтожен...\n\n";
}

void AI::controller(Player& player)
{
	if (status)
	{
		if (!canAttack)
		{
			auto path = generator.findPath({ pos_x, pos_y }, { player.getPos_x(), player.getPos_y() });

			size_t i = path.size()-2;
			if (i > 0)
			{
				pos_x = path[i].x;
				pos_y = path[i].y;
			}
			else
				canAttack = true;
		}
		else
			player.getDamage(attack());
	}
}

void AI::collision(std::vector<int> walls, int width, int height)
{
	generator.setWorldSize({ width, height });
	for (int i = 0; i < walls.size() - 1; i += 2)
		generator.addCollision({ walls[i], walls[i + 1] });
}