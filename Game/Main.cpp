#include <iostream>
#include <conio.h>
#include <windows.h>
#include "World.h"

#include "Units.h"

#define gameloop while(true)

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
    landscape.generator(seed, 0, 0);

    int mapIndex_x = 0, 
        mapIndex_y = 0;

    gameloop
    {
        landscape.draw();
        char ch = _getch();

        switch (ch)
        {
        case 'w':
            mapIndex_y--;
            break;
        case 'a':
            mapIndex_x--;
            break;
        case 's':
            mapIndex_y++;
            break;
        case 'd':
            mapIndex_x++;
            break;
        }
        landscape.generator(seed, mapIndex_x, mapIndex_y);
        landscape.clean();
    }
    return 0;
}