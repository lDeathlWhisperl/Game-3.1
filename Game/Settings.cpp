#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>

#include "Game.h"
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

static int foundSetting(char *search)
{
    int parametr = 0;
    std::ifstream fin("settings.txt");
    char buffer[1024];

    while(fin.getline(buffer, 1024, ':'))
        if (strstr(buffer, search))
            fin >> parametr;

    return parametr;
}

void Settings::write(char *setting_type, unsigned int setting_num)
{
    size_t num_count = std::to_string(setting_num).size();
    size_t i = general_settings.find(setting_type) + 10;

    general_settings.erase(i, num_count);
    general_settings.insert(i, std::to_string(setting_num));
}

int Settings::menu_id = 0,
    Settings::choice = -1;

const int Settings::BUTTON_COUNT = 6;

static bool back = false;

char Settings::settings[BUTTON_COUNT][33] =
{
    "[             Back             ]",
    "[            Logging           ]",
    "[ Change world generation seed ]",
    "[           Nickname           ]",
    "[       set HUD position       ]",
    "[            Penguin           ]"
};

std::string Settings::general_settings = "";

void Settings::menu()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    int x, y;
    getConsoleScreenSize(x, y);
    x /= 2;
    y /= 2;
               
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        Position.X = x - 16;
        Position.Y = y - BUTTON_COUNT / 2;
        SetConsoleCursorPosition(hOut, Position);

        if (i == menu_id) std::cout << "\x1b[102m\x1b[30m";
        std::cout << settings[i] << "\x1b[0m\n";
        y += 2;
    }

    std::ofstream fout("settings.txt");
    fout << general_settings;
}

void Settings::logging()
{
    int log_type;

    char ch[] = "Log type";
    log_type = foundSetting(ch);
    std::cout << log_type;

    if (log_type < 0 || log_type > 2) log_type = 0;

    switch (log_type)
    {
    case 0:
        log_type++;
        strcpy_s(settings[1], "[         FILE LOGGING         ]");
        break;
    case 1:
        log_type++;
        strcpy_s(settings[1], "[       TERMINAL LOGGING       ]");
        break;
    case 2:
        log_type = 0;
        strcpy_s(settings[1], "[        WITHOUT LOGGING       ]");
        break;
    }

    write(ch, log_type);
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
    case BUTTON_COUNT - 1:
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
    std::ifstream fin("settings.txt");
    char buffer[512];
    while (fin.getline(buffer, 512)) 
    {
        general_settings += buffer;
        general_settings += '\n';
    }
    fin.close();

    back = false;

    while (true)
    {
        system("cls");
        menu();
        controller();
        if (back) break;
    }    
}