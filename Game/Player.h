#pragma once

#include "Character.h"
#include <conio.h>

class Player : public Character
{
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

    char lastPressedKey = '\0';
public:
    Player();

    ~Player();

    void controller(int, int, int, int);

    void getDamage(int);

    void controller();

    char showPlayer();

    char getLastPressedKey();
};