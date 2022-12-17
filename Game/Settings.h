#pragma once

class Settings
{
    static int menu_id;

    static int choice;

    static const int BUTTON_COUNT;

    static char settings[][33];

    static std::string general_settings;

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

    static void menu();

    static void controller();

    static void logging();

    static void mode();

    static void write(char*, unsigned int);

    Settings() {};
public:
    static void init();
};