//#include <iostream>
#include <windows.h>

#include "World.h"
#include "Render.h"
#include "Player.h"

#define gameLoop() while(true)

void fullscreen()
{
    ShowWindow(GetForegroundWindow(), SW_SHOWMAXIMIZED);
}

void fontSize(int num)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX fontInfo;

    fontInfo.cbSize = sizeof(fontInfo);

    GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);

    wcscpy_s(fontInfo.FaceName, L"Lucida Console");

    fontInfo.dwFontSize.Y = num;
    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
}

int main()
{
    fullscreen();
    int x = 177, y = 51;
    unsigned int seed = 17042003;

    //fontSize(5);

    World landscape(x, y);
    Render render;
    Player player;

    landscape.generator(seed, 0, 0);
    
    gameLoop()
    {
        render.draw(landscape, player);

        player.controller();
        landscape.generator(seed, player.getPos_x(), player.getPos_y());

        render.clean();
    }
    return 0;
}