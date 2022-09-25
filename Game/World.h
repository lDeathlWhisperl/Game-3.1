#pragma once

#include <vector>

class World
{
private:
	char tile = 219;
	std::vector<int> vertexes;

	void landscape(int, int);

	std::string paint(int);

	std::vector<int> diamond(int, int, int, int, int);

public:
	void generator(int, int);

	void draw(int, int);

	void clean();
};