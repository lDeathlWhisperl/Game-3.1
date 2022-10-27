#pragma once

#include "Actor.h"

#include <iostream>

class Base : public Actor
{
public:
	Base(int x, int y);

	void offset(char);

	void show();

	bool operator==(Base);

	bool operator<(Base);
};