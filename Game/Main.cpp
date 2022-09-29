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
    int x = 321, y = 90;

    World landscape(x, y);
    landscape.generator();

    landscape.draw();

    return 0;
}
