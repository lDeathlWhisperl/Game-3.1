#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

#include "Settings.h"
#include "Penguin.h"

static void getConsoleScreenSize(int& x, int& y)
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


int Settings::menu_id = 0,
    Settings::choice = -1;

const int Settings::BUTTON_COUNT = 5;

static bool back = false;

void Settings::menu()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    int x, y;
    getConsoleScreenSize(x, y);
    x /= 2;
    y /= 2;

    char settings[BUTTON_COUNT][33] =
    {
        "[             Back             ]",
        "[            Logging           ]",
        "[ Change world generation seed ]",
        "[           Nickname           ]",
        "[            Penguin           ]"
    };

    Position.X = x - 16;
    Position.Y = y++;
    SetConsoleCursorPosition(hOut, Position);

    for (int i = 0; i < 36; i++) std::cout << (unsigned char)219;

    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        Position.X = x - 16;
        Position.Y = y++;
        SetConsoleCursorPosition(hOut, Position);

        std::cout << (unsigned char)219 << ' ';
        if (i == menu_id) std::cout << "\x1b[102m";
        std::cout << settings[i] << "\x1b[0m" << ' ' << (unsigned char)219 << '\n';
    }

    Position.X = x - 16;
    Position.Y = y;
    SetConsoleCursorPosition(hOut, Position);

    for (int i = 0; i < 36; i++) std::cout << (unsigned char)219;
}

int log_type = 0;

void Settings::logging()
{
    system("cls");
    std::cout << "Logging type has been changed to ";
    switch (log_type)
    {
    case 0:
        log_type++;
        std::cout << "[FILE LOGGING]\n";
        break;
    case 1:
        log_type++;
        std::cout << "[TERMINAL LOGGING]\n";
        break;
    case 2:
        log_type = 0;
        std::cout << "[WITHOUT LOGGING]\n";
        break;
    }
    std::ofstream fout("Settings.txt");
    fout << log_type;

    system("pause");
}

//put code here
void Settings::mode()
{
    switch (choice)
    {
    case 0:
        back = true;
        break;
    case 1:
        logging();
        break;
    case 4:
        Penguin::draw();
        break;
    }
    choice = -1;
}

void Settings::controller()
{
    char ch = _getch();

    switch (ch)
    {
    case w:
    case W:
    case ARROW_UP:
        if (menu_id != 0) menu_id--;
        else menu_id = BUTTON_COUNT-1;
        break;
    case s:
    case S:
    case ARROW_DOWN:
        if (menu_id != BUTTON_COUNT-1) menu_id++;
        else menu_id = 0;
        break;
    case SPACE:
    case ENTER:
        choice = menu_id;
        break;
    case ESC:
        choice = 0;
    }

    mode();
}

void Settings::init()
{
    while (true)
    {
        system("cls");
        menu();
        controller();
        if (back) break;
    }
}