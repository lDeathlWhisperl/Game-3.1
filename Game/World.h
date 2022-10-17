#pragma once

#include <vector>

class World
{
private:
	int length, width;
	std::vector<std::vector<double>> map;

	void landscape();

	void plantTree(int, int);

	void plantCactus(int, int);

public:
	World(int l, int w) : length(l), width(w){}

	void generator(unsigned int, int, int);

	std::vector<std::vector<double>> getMap();

	int x();

	int y();
};