#pragma once

#include "Actor.h"

#include <conio.h>
#include <iostream>

class Player : public Actor
{
	char character = '^';

public:
    void controller();

    char showPlayer();

    void getDamage(int);
};