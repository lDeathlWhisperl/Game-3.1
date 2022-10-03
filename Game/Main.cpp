#include <iostream>
#include <windows.h>
#include "World.h"

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
    int x = 177, y = 52;

    //fontSize(5);

    World landscape(x, y);
    landscape.generator(17042003);

    landscape.draw();
    
    return 0;
}