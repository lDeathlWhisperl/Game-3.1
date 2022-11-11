#include <windows.h>

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
//debug only
void colors()
{
    for (int i = 0; i < 100; i++)
        std::cout << "\x1b[" << i << "m" << (char)219 << ' ' << i << "\x1b[0m\n";
}

int main()
{
    fullscreen();
    int x, y;
    unsigned int seed = 17042003;
    getConsoleScreenSize(x, y);

    World landscape(x+17, y+8);
    Player player;

    landscape.landscape();
    landscape.generator(seed, 0, 0);
    //colors();
    //exit(0);
    gameLoop()
    {
        Render::draw_world(landscape, player);

        player.controller();
        landscape.generator(seed, player.getPos_x(), player.getPos_y());

        if (!player.getStatus())
            game_over;

        Render::update();
    }
    return 0;
}