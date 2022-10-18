#pragma once

#include "Actor.h"

#include <conio.h>

class Player : public Actor
{
	char character = '^';

public:
    void controller();

    char showPlayer();
};