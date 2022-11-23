#include "AI.h"

AStar::Generator AI::generator;

void AI::controller(Player& player)
{
	if (status)
	{
		int player_index = player.getPos_x() + player.getPos_y();
		int monster_index = pos_x + pos_y;
		int difference = monster_index - player_index;
		if (difference < 0) difference *= -1;

		if (difference > 0)
		{
			auto path = generator.findPath({ pos_x, pos_y }, { player.getPos_x(), player.getPos_y() });

			size_t i = path.size() - 2;
			if (i > 0)
			{
				pos_x = path[i].x;
				pos_y = path[i].y;
			}
		}
		else
			player.getDamage(attack());
	}
	else
		generator.clearCollisions();
}

void AI::collision(std::vector<int> walls, int width, int height)
{
	generator.setWorldSize({ width, height });
	for (int i = 0; i < walls.size() - 1; i += 2)
		generator.addCollision({ walls[i], walls[i + 1] });

	//generator.setHeuristic(AStar::Heuristic::octagonal);
}