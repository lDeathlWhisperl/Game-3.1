#pragma once

#include <vector>

class World
{
private:
	char tile = 219;
	std::vector<std::vector<int>> vertexes;

	void generator(int, int);

	void landscape(int, int);

	std::string paint(int);

	void dimond(int, int, int, int, int);

public:
	void draw(int, int);

	void clean();
};