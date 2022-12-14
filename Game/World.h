#pragma once

class World
{
private:
	int length, width;
	double** map;

	void plantTree(int, int);

	void plantCactus(int, int);

public:
	World(int, int);

	~World();

	void landscape();

	void generator(unsigned int, int, int);
	
	double getMap(int, int);

	int getLength();

	int getWidth();
};