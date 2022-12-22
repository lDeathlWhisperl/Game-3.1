#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>

#include "Game.h"
#include "Settings.h"
#include "Penguin.h"

//
int Settings::sett_logType = 0;
unsigned int Settings::sett_HUD_x = 0, Settings::sett_HUD_y = 0;
std::string Settings::sett_nickname = "[NULL]";
//

int Settings::menu_id = 0,
    Settings::choice = -1;

const int Settings::BUTTON_COUNT = 7;

static bool out = false;

char Settings::settings[BUTTON_COUNT][33] =
{
    "[             Back             ]",
    "[            Logging           ]",
    "[ Change world generation seed ]",
    "[     Set random world seed    ]",
    "[           Nickname           ]",
    "[       Set HUD position       ]",
    "[            Penguin           ]"
};

void Settings::menu()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    int x, y;
    Game::getConsoleScreenSize(x, y);
    x /= 2;
    y /= 2;
               
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        Position.X = x - 16;
        Position.Y = y - BUTTON_COUNT / 2;
        SetConsoleCursorPosition(hOut, Position);

        if (i == menu_id) std::cout << "\x1b[102m\x1b[30m";
        std::cout << settings[i] << "\x1b[0m\n";
        y += 2;
    }
}

void Settings::logging()
{
    switch (sett_logType)
    {
    case 0:
        sett_logType++;
        strcpy_s(settings[1], "[         FILE LOGGING         ]");
        break;
    case 1:
        sett_logType++;
        strcpy_s(settings[1], "[       TERMINAL LOGGING       ]");
        break;
    case 2:
        strcpy_s(settings[1], "[        WITHOUT LOGGING       ]");
    default:
        sett_logType = 0;
    }
}

void Settings::setSeed()
{
    system("cls");

    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    int x, y;
    Game::getConsoleScreenSize(x, y);
    x /= 2;
    y /= 2;

    Position.X = x - 18;
    Position.Y = y;
    SetConsoleCursorPosition(hOut, Position);
    std::cout << "Enter the new world generation seed: ";
    std::cin >> Game::seed;
}

void Settings::setRandomSeed()
{
    srand(unsigned(time(0)));
    Game::seed = static_cast<unsigned int>(rand());
}

void Settings::setNickname()
{
    system("cls");

    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    int x, y;
    Game::getConsoleScreenSize(x, y);
    x = x / 2 - 22;
    y /= 2;

    Position.X = x;
    Position.Y = y;
    SetConsoleCursorPosition(hOut, Position);

    std::cout << "Set the new nickname: " << sett_nickname << " -> ";
    std::getline(std::cin, sett_nickname);
}

void Settings::setHUDPosition()
{
    system("cls");

    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    int x, y;
    Game::getConsoleScreenSize(x, y);

    Position.X = x / 2 - 10;
    Position.Y = y / 2;
    SetConsoleCursorPosition(hOut, Position);

    std::cout << "Set new HUD position\n";
    Position.X = x / 2 - 10;
    Position.Y = (y / 2) + 1;
    SetConsoleCursorPosition(hOut, Position);

    std::cout << "X: ";
    std::cin >> sett_HUD_x;
    Position.X = x / 2 - 10;
    Position.Y = (y / 2) + 2;
    SetConsoleCursorPosition(hOut, Position);

    std::cout << "Y: ";
    std::cin >> sett_HUD_y;

    if (sett_HUD_x > (unsigned int)x - 27) sett_HUD_x = 0;
    if (sett_HUD_y > (unsigned int)y - 5) sett_HUD_y = 0;
}

void Settings::mode()
{
    switch (choice)
    {
    case 0:
        out = true;
        break;
    case 1:
        logging();
        break;
    case 2:
        setSeed();
        break;
    case 3:
        setRandomSeed();
        break;
    case 4:
        setNickname();
        break;
    case 5:
        setHUDPosition();
        break;
    case BUTTON_COUNT - 1:
        Penguin::draw();
        break;
    }
    choice = -1;
}

void Settings::controller()
{
    char ch = _getch();

    switch (ch)
    {
    case w:
    case W:
    case ARROW_UP:
        if (menu_id != 0) menu_id--;
        else menu_id = BUTTON_COUNT-1;
        break;
    case s:
    case S:
    case ARROW_DOWN:
        if (menu_id != BUTTON_COUNT-1) menu_id++;
        else menu_id = 0;
        break;
    case SPACE:
    case ENTER:
        choice = menu_id;
        break;
    case ESC:
        choice = 0;
    }

    mode();
}

void Settings::init()
{
    out = false;

    while (!out)
    {
        system("cls");
        menu();
        controller();
    }    
}