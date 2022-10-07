#pragma once

#include <vector>

class World
{
private:
	unsigned char tile = 219;
	int length, width;
	std::vector<std::vector<double>> map;

	void landscape();

	void plantTree(int, int);

	std::string paint(double);

public:
	World(int l, int w) : length(l), width(w){}

	void generator(unsigned int, int, int);

	void draw();

	void clean();
};