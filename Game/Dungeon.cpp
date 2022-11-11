#include "Dungeon.h"

bool Dungeon::Room::intersect(const Room& r) const
{
	return !(r.x >= (x + width) || x >= (r.x + r.width) || r.y >= (y + height) || y >= (r.y + r.height));
}

void Dungeon::generate(int roomsCount) {
	d_rooms.clear();

	for (int i = 0; i < roomsCount; ++i)
		for (int j = 0; j < 1000; ++j)
		{
			const int w = 10 + rand() % 31, h = 10 + rand() % 31;

			const Room room = { 3 + rand() % (d_width - w - 6), 3 + rand() % (d_height - h - 6), w, h };

			auto intersect = std::find_if(std::begin(d_rooms), std::end(d_rooms), [&room](const Room& r)
				{
					return room.intersect(r);
				});

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
	
	Point start, end;

	for (int i = 0; i < d_rooms.size() - 1; i++)
	{
		start.x = d_rooms[i].x + d_rooms[i].width / 2;
		start.y = d_rooms[i].y + d_rooms[i].height / 2;

		end.x = d_rooms[i + 1].x + d_rooms[i + 1].width / 2;
		end.y = d_rooms[i + 1].y + d_rooms[i + 1].height / 2;
		generatePassage(start, end);
	}

	int x = d_rooms[0].x + d_rooms[0].width / 2,
		y = d_rooms[0].y - 1;

	d_data[x + y * d_width] = 1;
	y--;
	d_data[x + y * d_width] = 3;

	generateWalls();
}

int Dungeon::get(int x, int y)
{
	return d_data[x + y * d_width];
}

void Dungeon::generatePassage(const Point& start, const Point& finish)
{
	AStar::Generator generator;
	generator.setWorldSize({ d_width, d_height });
	generator.setHeuristic(AStar::Heuristic::euclidean);
	generator.setDiagonalMovement(false);
	auto path = generator.findPath({ start.x, start.y }, { finish.x, finish.y });

	for (auto& coordinate : path)
	{
		int index = coordinate.y * d_width + coordinate.x;
		d_data[index] = 1;
	}
}

void Dungeon::generateWalls() {
	static const int offsets[8][2] = 
	{
		{-1,-1}, { 0,-1}, { 1,-1}, { 1, 0},
		{ 1, 1}, { 0, 1}, {-1, 1}, {-1, 0},
	};

	for (int x = 1; x < d_width - 1; ++x)
		for (int y = 1; y < d_height - 1; ++y)
			if (d_data[x + y * d_width] == 0)
				for (int i = 0; i < 8; ++i)
					if (d_data[(x + offsets[i][0]) + (y + offsets[i][1]) * d_width] == 1)
					{
						d_data[x + y * d_width] = 2;
						break;
					}
}

int Dungeon::getHeight()
{
	return d_height;
}

int Dungeon::getWidth()
{
	return d_width;
}

int Dungeon::getStart_x()
{
	if (!d_rooms.empty())
		return d_rooms[0].x + d_rooms[0].width / 2;
	return 0;
}

int Dungeon::getStart_y()
{
	if (!d_rooms.empty())
		return d_rooms[0].y - 1;
	return 0;
}

bool Dungeon::isExit()
{
	return exit;
};

void Dungeon::Exit()
{
	exit = true;
}