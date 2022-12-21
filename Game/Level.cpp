#include "Level.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>

int Level::choice = -1;
int Level::menu_id = 1;
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
        return cost[i] = player->getMaxHP() + 1;
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
        return player->getMaxHP() + 1;
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

    char field[][19] =
    {
        " Restore HP       ",
        " Restore armor    ",
        " Incrase max HP   ",
        " Incrase strength "
    };

    int stats[4] =
    {
        player->getHP(), player->getArmor(), player->getMaxHP(), player->getStrength()
    };

    int length = player->getMaxHP();

    for (int i = 0; i < 37; i++) std::cout << (char)219;
    std::cout << '\n';

    std::cout.setf(std::ios::left);
    std::cout << "\x1b[4m" << (char)219 << ' ' << std::setw(6) << player->getMoney() << "$          lvl    up   cost " << (char)219 << "\x1b[0m\n";

    for (int i = 0; i < 4; i++)
    {
        std::cout << (char)219;
        if (i == menu_id) std::cout << "\x1b[102m\x1b[30m";
        std::cout << field[i] << std::setw(4) << stats[i] << "-> " << std::setw(4) << potential(i) << ' ' << std::setw(5) << calcCost(i) << "\x1b[0m" << (char)219 << '\n';
    }
    std::cout.unsetf(std::ios::left);
    for (int i = 0; i < 37; i++) std::cout << (char)219;
}

void Level::mode()
{
    switch (choice)
    {
    case 1:
        restoreHP();
        break;
    case 2:
        restoreArmor();
        break;
    case 3:
        incraseHP();
        break;
    case 4:
        incraseStrength();
        break;        
    }
    choice = -1;
}

void Level::restoreHP()
{

}

void Level::restoreArmor()
{

}

void Level::incraseHP()
{

}

void Level::incraseStrength()
{

}

void Level::upgrade(Player &pl)
{
    player = &pl;
    out = false;
    while(!out)
    {
        menu();
        controller();
    }
}