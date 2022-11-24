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

class Dungeon
{
	std::vector<int> d_data, walls_coords;
	std::vector<Room> d_rooms; 
	
	int startPoint_x, startPoint_y;
	int d_width, d_height;
	bool out = false;

	void generatePassage(const Point&, const Point&);

	int getRandomNumber(int, int);

	AI* spawn(int, int);

	void generateWalls();
public:
	AI* monsters[8] = {};

	Dungeon(int width, int height) : d_width(width), d_height(height-1)
	{
		d_data.resize(width * height, 0);
		startPoint_x = 0;
		startPoint_y = 0;

		std::ofstream fout("log.txt");
		fout
			<< "d_data:       " << sizeof(d_data) << '\n'
			<< "walls_coords: " << sizeof(walls_coords) << '\n'
			<< "d_rooms:      " << sizeof(d_rooms) << '\n'
			<< "startPoint_x: " << sizeof(startPoint_x) << '\n'
			<< "startPoint_y: " << sizeof(startPoint_y) << '\n'
			<< "d_width:      " << sizeof(d_width) << '\n'
			<< "d_height:     " << sizeof(d_height) << '\n'
			<< "out:          " << sizeof(out);
	}

	~Dungeon()
	{
		for (AI* m : monsters)
			m->~AI();
		d_data.clear();
		walls_coords.clear();
		d_rooms.clear();
	}

	void generate(int);

	int get(int, int);

	int getWidth();

	int getHeight();

	int spawn_x();

	int spawn_y();

	bool isExit();

	void Exit();
};