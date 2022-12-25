#pragma once

#include "Player.h"

class Level final
{
    static int choice;
    static int menu_id;
    static int cost[4];

    static Player* player;

    enum buttons
    {
        //spec
        ENTER = 13,
        ESC   = 27,
        SPACE = 32,
        //arrows
        ARROW_UP   = 72,
        ARROW_DOWN = 80,
        //controllers
        I = 73,
        S = 83,
        W = 87,

        i = 105,
        s = 115,
        w = 119,
    };

    static void controller();

    static void menu();

    static int potential(int);

    static int calcCost(int);

    static void mode();

    static void restoreHP();

    static void restoreArmor();

    static void increaseHP();

    static void increaseStrength();
public:
	static void upgrade(Player&);
};