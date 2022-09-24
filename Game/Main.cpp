#include <iostream>
#include <conio.h>
#include <windows.h>
#include "World.h"

void fullscreen()
{
    ShowWindow(GetForegroundWindow(), SW_SHOWMAXIMIZED);
}

int main()
{
    fullscreen();
    World landscape;

    int size = 32;

    //while (true)
    //{
    //  landscape.clean();
    landscape.draw(size, size);
    //char c = _getch();
    //    if (c == 'x') break;
    //}

    return 0;
}
