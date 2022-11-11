#pragma once

#include "Character.h"
#include "Base.h"

#include <conio.h>
#include <iostream>
#include <vector>

class Player : public Character
{
    char lastPressedKey = '\0';
    std::vector<Base> base;
    bool isDamaged = false;
    int top_collision_index   = -1,
        left_collision_index  = -1,
        right_collision_index = -1,
        bottom_collision_index = -1;

    enum buttons
    {
        //spec
        ENTER = 13,
        ESC   = 27,
        SPACE = 32,
        //arrows
        ARROW_UP    = 72,
        ARROW_LEFT  = 75,
        ARROW_RIGHT = 77,
        ARROW_DOWN  = 80,
        //controllers
        A = 65,
        D = 68,
        E = 69,
        Q = 81,
        S = 83,
        W = 87,

        a = 97,
        d = 100,
        e = 101,
        q = 113,
        s = 115,
        w = 119,
    };
public:
    Player();

    bool placeBase(int, int, bool, bool&);

    void collision(int top, int left, int right, int bottom)
    {
        top_collision_index   = top;
        left_collision_index  = left;
        right_collision_index = right;
        bottom_collision_index = bottom;

    }

    void breakBase(int, int, bool);

    void getDamage(int);

    void controller();

    char showPlayer();

    char getLastPressedKey();

};