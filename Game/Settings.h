#pragma once

#include "Adapter.h"
#include "HUD.h"
#include "Level.h"

class Settings
{
    static int sett_logType;
    static std::string sett_nickname;
    static unsigned int sett_HUD_x, sett_HUD_y;

    static int menu_id;

    static int choice;

    static const int BUTTON_COUNT;

    static char settings[][33];

    enum buttons
    {
        //spec
        ENTER = 13,
        ESC = 27,
        SPACE = 32,
        //arrows
        ARROW_UP = 72,
        ARROW_DOWN = 80,
        //controllers
        S = 83,
        W = 87,

        s = 115,
        w = 119,
    };

    static void menu();

    static void controller();

    static void logging();

    static void setSeed();

    static void setRandomSeed();

    static void setNickname();

    static void setHUDPosition();

    static void mode();

    friend Adapter;
    friend HUD;
    friend Level;

    Settings() {};
public:
    static void init();
};