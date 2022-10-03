#pragma once

#include <vector>

class World
{
private:
	char tile = 219;
	int length, width;
	std::vector<std::vector<double>> polygons;

	void landscape();

	void smooth();

	void plantTree(int, int);

	std::string paint(double);

public:
	World(int l, int w) : length(l), width(w){}

	void generator(long long int);

	void draw();

	void clean();
};