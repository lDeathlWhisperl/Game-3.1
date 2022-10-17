#pragma once

#include "World.h"

#include <iostream>

class Render
{
	std::string paint(double);
public:
	void draw(World);

	void clean();
};