#pragma once

#include "Monster.h"

struct Room
{
	int x, y, width, height;

	bool intersect(const Room& r) const;
};

struct Point
{
	int x, y, cost;

	bool operator==(const Point& p) const
	{
		return x == p.x && y == p.y;
	}

	bool operator<(const Point& p) const
	{
		return cost > p.cost;
	}
};

struct Range
{
	int min, max;
};

class Dungeon final
{
	std::vector<int> d_data, walls_coords;
	std::vector<Room> d_rooms; 
	
	int startPoint_x, startPoint_y;
	int d_width, d_height;
	bool out = false;

	void generatePassage(const Point&, const Point&);

	AI* spawn(int, int);

	void generateWalls();
public:
	AI* monsters[8] = {};

	Dungeon(int, int);

	~Dungeon();

	void generate(int, Range, Range);

	int getVertex(int, int);

	int getWidth();

	int getHeight();

	int spawn_x();

	int spawn_y();

	bool isExit();

	void Exit();
};