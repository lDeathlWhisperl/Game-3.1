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

    int size = 65;
    landscape.generator(size, size);


    landscape.draw(size, size);
    //landscape.draw(size, size);

    return 0;
}
