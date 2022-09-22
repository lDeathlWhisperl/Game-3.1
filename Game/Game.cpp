#include <iostream>
#include <conio.h>
#include "World.h"

int main()
{
    World landscape;

    while (true)
    {
        //landscape.clean();
        landscape.draw(211, 50);
        char c = _getch();

        if (c == 'x') break;
    }

    return 0;
}
