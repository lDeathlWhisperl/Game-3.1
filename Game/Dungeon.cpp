#include "Dungeon.h"
#include "Logging.h"
#include <queue>

int getRandomNumber(int min, int max)
{
	return min + rand() % (max - min + 1);
}

Dungeon::Dungeon(int width, int height) : d_width(width), d_height(height - 1)
{
	d_data.resize(width * height, 0);
	startPoint_x = 0;
	startPoint_y = 0;
	
	debug::log->request("Player intered into the dungeon\n\n");
}

Dungeon::~Dungeon()
{
	debug::log->request("Player leaved the dungeon\n\n");
	for (AI* m : monsters) m->~AI();
	d_data.clear();
	walls_coords.clear();
	d_rooms.clear();
}

bool Room::intersect(const Room& r) const
{
	return !(r.x >= (x + width) || x >= (r.x + r.width) || r.y >= (y + height) || y >= (r.y + r.height));
}

void Dungeon::generate(int roomsCount, Range rang, Range monster) {
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

			if (intersect == std::end(d_rooms)) 
			{
				d_rooms.push_back(room);
				break;
			}
		}

	d_data.assign(d_width * d_height, 6);

	for (const Room& room : d_rooms)
		for (int x = 0; x < room.width; ++x)
			for (int y = 0; y < room.height; ++y)
				d_data[(room.x + x) + (room.y + y) * d_width] = 7;
		
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

	d_data[x + y * d_width] = 7;
	y--;
	d_data[x + y * d_width] = 5;

	generateWalls();
	AI::collision(walls_coords, d_width, d_height);

	int room = 1;
	for (int i = 1; i < 9; i++)
	{
		monsters[i - 1] = spawn(getRandomNumber(rang.min, rang.max), getRandomNumber(monster.min, monster.max));
		if (i % 2 == 0)
		{
			monsters[i - 1]->setPos_x(d_rooms[room].x);
			monsters[i - 1]->setPos_y(d_rooms[room].y);
			room++;
		}
		else
		{
			monsters[i - 1]->setPos_x(d_rooms[room].x + d_rooms[room].width - 1);
			monsters[i - 1]->setPos_y(d_rooms[room].y + d_rooms[room].height - 1);
		}
	}
	startPoint_x = d_rooms[0].x + d_rooms[0].width / 2;
	startPoint_y = d_rooms[0].y - 1;
	
	walls_coords.clear();
	d_rooms.clear();
}

int Dungeon::getVertex(int x, int y)
{
	return d_data[x + y * d_width];
}

void Dungeon::generatePassage(const Point& start, const Point& finish)
{
	AStar::Generator generator;
	generator.setWorldSize({ d_width, d_height });

	auto path = generator.findPath({ start.x, start.y }, { finish.x, finish.y });

	for (auto& coordinate : path)
	{
		int index = coordinate.y * d_width + coordinate.x;
		d_data[index] = 7;
	}
}

AI* Dungeon::spawn(int rang, int monster)
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
	delete spawner;
	return ai;
}

void Dungeon::generateWalls() {
	static const int offsets[8][2] =
	{
		{-1,-1}, { 0,-1}, { 1,-1}, { 1, 0},
		{ 1, 1}, { 0, 1}, {-1, 1}, {-1, 0},
	};

	for (int x = 1; x < d_width - 1; ++x)
		for (int y = 1; y < d_height - 1; ++y)
			if (d_data[x + y * d_width] == 6)
				for (int i = 0; i < 8; ++i)
					if (d_data[(x + offsets[i][0]) + (y + offsets[i][1]) * d_width] == 7)
					{
						d_data[x + y * d_width] = 3;
						walls_coords.push_back(x);
						walls_coords.push_back(y);
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

int Dungeon::spawn_x()
{
	return startPoint_x;
}

int Dungeon::spawn_y()
{
	return startPoint_y;
}

bool Dungeon::isExit()
{
	return out;
};

void Dungeon::Exit()
{
	out = true;
}