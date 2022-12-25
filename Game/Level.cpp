#include "Level.h"
#include "Settings.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>

int Level::choice = -1;
int Level::menu_id = 0;
int Level::cost[4];
Player* Level::player;

static bool out;

void getConsoleScreenSize(int& x, int& y)
{
    HANDLE hWndConsole;
    if (hWndConsole = GetStdHandle(-12))
    {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
        {
            x = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
            y = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
        else
            printf("Error: %d\n", GetLastError());
    }
    else
        printf("Error: %d\n", GetLastError());
}

void Level::controller()
{
    char ch = _getch();
    switch (ch)
    {
    case w:
    case W:
    case ARROW_UP:
        if (menu_id != 0) menu_id--;
        else menu_id = 3;
        break;
    case s:
    case S:
    case ARROW_DOWN:
        if (menu_id != 3) menu_id++;
        else menu_id = 0;
        break;
    case SPACE:
    case ENTER:
        choice = menu_id;
        break;
    case i:
    case I:
    case ESC:
        out = true;
    }
}

int Level::calcCost(int i)
{
    switch (i)
    {
    case 0:
        return cost[i] = 5;
    case 1:
        return cost[i] = 10;
    case 2:
        int x, y;
        getConsoleScreenSize(x, y);
        return (player->getMaxHP() == x - Settings::sett_HUD_x - 2) ? cost[i] = 0 : cost[i] = player->getMaxHP() + 1;
    case 3:
        return cost[i] = player->getStrength() + 2;
    default:
        return - 1;
    }
}

int Level::potential(int i)
{
    switch (i)
    {
    case 0:
        return (player->getHP() + 1 > player->getMaxHP()) ? player->getMaxHP() : player->getHP() + 1;
    case 1:
        return (player->getArmor() + 1 > player->getMaxHP()) ? player->getMaxHP() : player->getArmor() + 1;
    case 2:
        int x, y;
        getConsoleScreenSize(x, y);
        return (player->getMaxHP() == x - Settings::sett_HUD_x - 2) ? x - Settings::sett_HUD_x - 2 : player->getMaxHP() + 1;
    case 3:
        return (player->getStrength() > 15) ? player->getStrength() : player->getStrength() + 1;
    default:
        return -1;
    }
}

void Level::menu()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    int x, y;

    getConsoleScreenSize(x, y);

    Position.X = 0;
    Position.Y = y-8;
    SetConsoleCursorPosition(hOut, Position);

    char field[][20] =
    {
        " Restore HP        ",
        " Restore armor     ",
        " Increase max HP   ",
        " Increase strength "
    };

    int stats[4] =
    {
        player->getHP(), player->getArmor(), player->getMaxHP(), player->getStrength()
    };

    int length = player->getMaxHP();

    for (int i = 0; i < 38; i++) std::cout << (char)219;
    std::cout << '\n';

    std::cout.setf(std::ios::left);
    std::cout << "\x1b[4m" << (char)219 << ' ' << std::setw(6) << player->getMoney() << "$           lvl    up   cost " << (char)219 << "\x1b[0m\n";

    for (int i = 0; i < 4; i++)
    {
        std::cout << (char)219;
        if (i == menu_id) std::cout << "\x1b[102m\x1b[30m";
        std::cout << field[i] << std::setw(4) << stats[i] << "-> " << std::setw(4) << potential(i) << ' ' << std::setw(5) << calcCost(i) << "\x1b[0m" << (char)219 << '\n';
    }
    std::cout.unsetf(std::ios::left);
    for (int i = 0; i < 38; i++) std::cout << (char)219;
}

void Level::mode()
{
    switch (choice)
    {
    case 0:
        restoreHP();
        break;
    case 1:
        restoreArmor();
        break;
    case 2:
        increaseHP();
        break;
    case 3:
        increaseStrength();
        break;        
    }
    choice = -1;
}

void Level::restoreHP()
{
    if (cost[0] <= player->getMoney() && player->getHP() != player->getMaxHP()) 
    {
        player->heal();
        player->setMoney(player->getMoney() - cost[0]);
    }
}

void Level::restoreArmor()
{
    if (cost[1] <= player->getMoney() && player->getArmor() != player->getMaxHP() / 2)
    {
        player->fixArmor();
        player->setMoney(player->getMoney() - cost[1]);
    }
}

void Level::increaseHP()
{
    int x, y;
    getConsoleScreenSize(x, y);
    if (cost[2] <= player->getMoney() && player->getMaxHP() < x - Settings::sett_HUD_x - 2)
    {
        player->increaseMaxHP();
        player->setMoney(player->getMoney() - cost[2]);
    }
}

void Level::increaseStrength()
{
    if (cost[3] <= player->getMoney())
    {
        player->increaseStrength();
        player->setMoney(player->getMoney() - cost[3]);
    }
}

void Level::upgrade(Player &pl)
{
    player = &pl;
    out = false;
    while(!out)
    {
        menu();
        controller();
        mode();
    }
}