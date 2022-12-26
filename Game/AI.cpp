#include "AI.h"
#include "Logging.h"

AStar::Generator AI::generator;
int AI::count = 0;

int mod(int x)
{
	return (x < 0) ? x * -1 : x;
}

AI::~AI()
{
	if (count == 1)
		generator.clearCollisions();
	count--;
	debug::log->request("[BOT] " + std::to_string(id) + " destroyed\n\n");
}

void AI::controller(Player& player)
{
	int abs_pos = pos_x - player.getPos_x() - pos_y + player.getPos_y();
	if (status && mod(abs_pos) < 10)
	{
		if (!canAttack)
		{
			auto path = generator.findPath({ pos_x, pos_y }, { player.getPos_x(), player.getPos_y() });

			size_t i = path.size() - 2;
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
	else
		canAttack = false;
}

void AI::collision(std::vector<int> walls, int width, int height)
{
	generator.setWorldSize({ width, height });
	for (int i = 0; i < walls.size() - 1; i += 2)
		generator.addCollision({ walls[i], walls[i + 1] });
}