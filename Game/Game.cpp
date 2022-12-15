#include <iomanip>
#include "Settings.h"
#include "Game.h"
#include "Logging.h"
#include "Render.h"

int Game::menu_id = 0,
    Game::choice = -1,
    Game::screen_size_x = 0,
    Game::screen_size_y = 0;

unsigned int Game::seed = 0;

static bool EXIT = false;

void Game::controller()
{
    char ch = _getch();

    switch (ch)
    {
    case w:
    case W:
    case ARROW_UP:
        if (menu_id != 0) menu_id--;
        else menu_id = 2;
        break;
    case s:
    case S:
    case ARROW_DOWN:
        if (menu_id != 2) menu_id++;
        else menu_id = 0;
        break;
    case SPACE:
    case ENTER:
        choice = menu_id;
        break;
    case ESC:
        choice = 2;
    }

    mode();
}

void Game::menu()
{
    char buttons[3][12] =
    {
        "[  PLAY   ]",
        "[ OPTIONS ]",
        "[  EXIT   ]"
    };

    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    int x = screen_size_x / 2,
        y = screen_size_y / 2;

    Position.X = x - 6;
    Position.Y = y++;
    SetConsoleCursorPosition(hOut, Position);

    for (int i = 0; i < 15; i++) std::cout << (unsigned char)219;

    for (int i = 0; i < 3; i++)
    {
        Position.X = x - 6;
        Position.Y = y++;
        SetConsoleCursorPosition(hOut, Position);

        std::cout << (unsigned char)219 << ' ';

        if (i == menu_id) std::cout << "\x1b[102m";
        std::cout << buttons[i] << "\x1b[0m " << (unsigned char)219;
    }

    Position.X = x - 6;
    Position.Y = y;
    SetConsoleCursorPosition(hOut, Position);

    for (int i = 0; i < 15; i++) std::cout << (unsigned char)219;
}

void Game::fullscreen()
{
    ShowWindow(GetForegroundWindow(), SW_SHOWMAXIMIZED);
}

void Game::getConsoleScreenSize(int& x, int& y)
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

void Game::game()
{
    debug::log->request("========================[New-game]=========================\n\n");
    debug::log->request("World generation seed: " + std::to_string(seed) + "\n\n");

    World landscape(screen_size_x + 16, screen_size_y + 8);
    Player player;

    landscape.landscape();
    landscape.generator(seed, 0, 0);

    /*gameLoop()
    {
        Render::draw_world(landscape, player);

        player.controller();

        landscape.generator(seed, player.getPos_x(), player.getPos_y());

        if (!player.getStatus())
            game_over;

        Render::update();
    }*/
}

void Game::settings()
{
    Settings::init();
}

void Game::mode()
{
    switch (choice)
    {
    case 0:
        game();
        break;
    case 1:
        settings();
        break;
    case 2:
        EXIT = true;
        break;
    }
    choice = -1;
}

void Game::init()
{
    fullscreen();
    srand(time(NULL));
    seed = static_cast<unsigned int>(rand());
    getConsoleScreenSize(screen_size_x, screen_size_y);

    while (true)
    {
        system("cls");
        menu();
        controller();
        if (EXIT) break;
    }

    debug::log->request("========================[Game-over]========================\n\n");
    delete debug::log;
}