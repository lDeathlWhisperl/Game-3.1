#pragma once

#include "Settings.h"

class Game
{
	static int menu_id;

    static int choice;

    static int screen_size_x, screen_size_y;

    static unsigned int seed;

    enum buttons
    {
        //spec
        ENTER = 13,
        ESC = 27,
        SPACE = 32,
        //arrows
        ARROW_UP = 72,
        ARROW_LEFT = 75,
        ARROW_RIGHT = 77,
        ARROW_DOWN = 80,
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

    static void controller();

    static void menu();

    static void fullscreen();

    static void getConsoleScreenSize(int& x, int& y);

    static void game();

    static void settings();

    static void mode();

    friend Settings;

    Game() {};
public:
    static void init();
};