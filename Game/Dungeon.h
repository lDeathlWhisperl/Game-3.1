#pragma once

#include <queue>

#include "Monster.h"

struct Point {
	int x, y, cost;

	bool operator==(const Point& p) const {
		return x == p.x && y == p.y;
	}

	bool operator<(const Point& p) const {
		return cost > p.cost;
	}
};

class Dungeon
{
public:
	struct Room
	{
		int x, y, width, height;

		bool intersect(const Room& r) const;
	};

	Dungeon(int width, int height) : d_width(width), d_height(height-1)
	{
		d_data.resize(width * height, 0);
	}

	void generate(int);

	int get(int, int);

	int getWidth();

	int getHeight();

	int spawn_x();

	int spawn_y();

	bool isExit();

	void Exit();

	AI* monsters[8] = {};
private:
	int d_width, d_height;
	std::vector<int> d_data;
	std::vector<Room> d_rooms;
	bool out = false;

	void generatePassage(const Point&, const Point&);

	void generateWalls();

	int getRandomNumber(int min, int max)
	{
		return min + rand() % (max - min + 1);
	}

	AI* spawn(int rang, int monster)
	{
		Spawner* spawner;
		AI* ai;
		switch (rang)
		{
		case 1:
			spawner = new Rang_1;
			break;
		case 2:
			spawner = new Rang_2;
			break;
		default:
			spawner = new Rang_3;
		}

		switch (monster)
		{
		case 1:
			ai = spawner->spawn_undead();
			break;
		case 2:
			ai = spawner->spawn_demon();
			break;
		default:
			ai = spawner->spawn_spirit();
		}
		return ai;
	}
};