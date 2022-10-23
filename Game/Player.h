#pragma once

#include "Character.h"
#include "Block.h"

#include <conio.h>
#include <iostream>
#include <vector>

class Player : public Character
{
	char character = '^',
        lastPressedKey = '\0';

public:
    void controller();

    char showPlayer();

    void getDamage(int);

    char getLastPressedKey();

    bool placeBlock(std::vector<Block>&, int, int, bool, bool&);
};