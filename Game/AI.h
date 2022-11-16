#pragma once

#include "AStar.hpp"
#include "Player.h"

#include <iostream>
#include <vector>

class AI : public Character
{
	AStar::Generator generator;
public:
	AI() : Character(1, 0, 1) {}

	AI(int hp, int arm, int str) : Character(hp, arm, str) {}

	void controller(Player& player)
	{
		if(status)
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

	void collision(std::vector<int> walls, int width, int height)
	{
		generator.setWorldSize({ width, height });
		for (int i = 0; i < walls.size() - 1; i += 2)
			generator.addCollision({ walls[i], walls[i + 1] });

		//generator.setHeuristic(AStar::Heuristic::octagonal);
	}

	virtual void draw() = 0 {}
};