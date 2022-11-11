#pragma once

#include <vector>
#include <queue>
#include <iostream>

#include "AStar.hpp"

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

	int getStart_x();

	int getStart_y();

	bool isExit();

	void Exit();

private:
	int d_width, d_height;
	std::vector<int> d_data;
	std::vector<Room> d_rooms;
	bool out = false;

	void generatePassage(const Point&, const Point&);

	void generateWalls();
};