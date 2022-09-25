#pragma once

#include <vector>

class World
{
private:
	char tile = 219;
	int length, width;
	std::vector<std::vector<int>> vertexes;

	void landscape();

	void smooth();

	std::string paint(int);

public:
	World(int l, int w) : length(l), width(w){}

	void generator();

	void draw();

	void clean();
};