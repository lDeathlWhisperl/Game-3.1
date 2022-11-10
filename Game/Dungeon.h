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

	int getWidth()
	{
		return d_width;
	}

	int getHeight()
	{
		return d_height;
	}

private:
	int d_width, d_height;
	std::vector<int> d_data;
	std::vector<Room> d_rooms;
	std::vector<std::vector<int>> temp;

	void generatePassage(const Point&, const Point&);

	void generateWalls();
};