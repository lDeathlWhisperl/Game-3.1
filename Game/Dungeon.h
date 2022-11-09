#pragma once

#include <vector>
#include <queue>
#include <iostream>

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

		bool intersect(const Room& r) const
		{
			return !(r.x >= (x + width) || x >= (r.x + r.width) || r.y >= (y + height) || y >= (r.y + r.height));
		}
	};

	Dungeon(int width, int height) : d_width(width), d_height(height-1)
	{
		d_data.resize(width * height, 0);
	}

	void generate(int roomsCount) {
		d_rooms.clear();
		
		for (int i = 0; i < roomsCount; ++i)
			for (int j = 0; j < 1000; ++j)
			{
				const int w = 10 + rand() % 31, h = 10 + rand() % 31;

				const Room room = { 3 + rand() % (d_width - w - 6), 3 + rand() % (d_height - h - 6), w, h };

				auto intersect = std::find_if(std::begin(d_rooms), std::end(d_rooms), [&room](const Room& r) {return room.intersect(r); });

				if (intersect == std::end(d_rooms)) {
					d_rooms.push_back(room);
					break;
				}
			}

		d_data.assign(d_width * d_height, 0);

		for (const Room& room : d_rooms) {
			for (int x = 0; x < room.width; ++x) for (int y = 0; y < room.height; ++y) {
				d_data[(room.x + x) + (room.y + y) * d_width] = 1;
			}
		}
		//
		Point start, end;

		start.x = d_rooms[0].x;
		start.y = d_rooms[0].y;
		
		end.x = d_rooms[d_rooms.size() - 1].x;
		end.y = d_rooms[d_rooms.size() - 1].y;
		//
		generatePassage(start, end);
		generateWalls();
	}

	void draw()
	{
		unsigned char tile = 219;
		for (size_t i = 1; i < d_data.size()+1; i++)
		{
			switch (d_data[i-1])
			{
			case 1:
				std::cout << "\x1b[90m" << tile << "\x1b[0m";
				break;
			case 2:
				std::cout << "\x1b[97m" << tile << "\x1b[0m";
				break;
			default:
				std::cout << ' ';
			}

			if (!(i % d_width)) std::cout << '\n';
		}
	}

private:
	int d_width, d_height;
	std::vector<int> d_data;
	std::vector<Room> d_rooms;

	void generatePassage(const Point& start, const Point& finish) 
	{
		std::vector<int> parents(d_width * d_height, -1);

		std::priority_queue<Point> active;
		active.push(start);

		static const int directions[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };
		while (!active.empty()) 
		{
			const Point point = active.top();
			active.pop();

			if (point == finish) break;

			for (int i = 0; i < 4; ++i) {
				Point p = { point.x - directions[i][0], point.y - directions[i][1], 0 };
				if (p.x < 0 || p.y < 0 || p.x >= d_width || p.y >= d_height)
					continue;

				if (parents[p.x + p.y * d_width] < 0) {
					p.cost = calcCost(p, finish);
					active.push(p);

					parents[p.x + p.y * d_width] = i;
				}
			}
		}

		Point point = finish;
		while (!(point == start)) {
			d_data[point.x + point.y * d_width] = 1;

			const int* directon = directions[parents[point.x + point.y * d_width]];
			point.x += directon[0];
			point.y += directon[1];
		}
	}

	void generateWalls() {
		static const int offsets[8][2] = {
			{-1,-1}, { 0,-1}, { 1,-1}, { 1, 0},
			{ 1, 1}, { 0, 1}, {-1, 1}, {-1, 0},
		};

		for (int x = 1; x < d_width - 1; ++x) for (int y = 1; y < d_height - 1; ++y) {
			if (d_data[x + y * d_width] == 0) for (int i = 0; i < 8; ++i) {
				if (d_data[(x + offsets[i][0]) + (y + offsets[i][1]) * d_width] == 1) {
					d_data[x + y * d_width] = 2;
					break;
				}
			}
		}
	}

	int calcCost(Point p, Point finish)
	{

	}
};