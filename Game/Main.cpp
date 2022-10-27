﻿#include <windows.h>

#include "Render.h"

#define gameLoop() while(true)
#define game_over break

void fullscreen()
{
    ShowWindow(GetForegroundWindow(), SW_SHOWMAXIMIZED);
}

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

int main()
{
    fullscreen();
    int x, y;
    unsigned int seed = 17042003;
    getConsoleScreenSize(x, y);

    World landscape(x, y-1);
    Render render;
    Player player;

    landscape.generator(seed, 0, 0);

    gameLoop()
    {
        render.draw(landscape, player);

        player.controller();
        landscape.generator(seed, player.getPos_x(), player.getPos_y());

        if (!player.getStatus())
            game_over;

        render.update();
    }
    return 0;
}