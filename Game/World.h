#pragma once

#include <list>
#include <iostream>

#include "Perlin.h"

class World
{
private:
	int length, width;
	double **map = new double*[width];

	void landscape();

	void plantTree(int, int);

	void plantCactus(int, int);

public:
	World(int l, int w) : length(l), width(w){}

	void generator(unsigned int, int, int);
	
	double getMap(int, int);

	int getLength();

	int getWidth();
};