#include "Player.h"
#include <algorithm>

bool exception(int num)
{
    switch (num)
    {
    case 6:
    case 3:
        return true;
    default:
        return false;
    }
}

Player::Player()
{
    character = '^';
    std::ofstream fout("log.txt", std::ios::app);
    fout << "Создание игрока...\n\n";
}

Player::~Player()
{
    std::ofstream fout("log.txt", std::ios::app);
    fout << "Удаление игрока...\n\n";
}

void Player::controller(int top, int left, int right, int bottom)
{
    char ch = '\0';
    if (_kbhit())
        ch = _getch();

    switch (ch)
    {
    case w:
    case W:
        if (!exception(top))
            pos_y--;
    case ARROW_UP:
        character = '^';
        break;
    case a:
    case A:
        if (!exception(left))
            pos_x--;
    case ARROW_LEFT:
        character = '<';
        break;
    case s:
    case S:
        if (!exception(bottom))
            pos_y++;
    case ARROW_DOWN:
        character = 'V';
        break;
    case d:
    case D:
        if (!exception(right))
            pos_x++;
    case ARROW_RIGHT:
        character = '>';
        break;
    case 'x':
        armor -= 5;
        getDamage(100);
    }

    lastPressedKey = ch;
}

void Player::controller()
{
    char ch = '\0';
    if (_kbhit())
        ch = _getch();

    switch (ch)
    {
    case w:
    case W:
            pos_y--;
    case ARROW_UP:
        character = '^';
        break;
    case a:
    case A:
            pos_x--;
    case ARROW_LEFT:
        character = '<';
        break;
    case s:
    case S:
            pos_y++;
    case ARROW_DOWN:
        character = 'V';
        break;
    case d:
    case D:
            pos_x++;
    case ARROW_RIGHT:
        character = '>';
        break;
    case 'x':
        armor -= 5;
        getDamage(100);
    }

    lastPressedKey = std::tolower(ch);
}

char Player::showPlayer()
{
    return character;
}

void Player::getDamage(int dmg)
{
    Character::getDamage(dmg);
    
    std::ofstream fout("log.txt", std::ios::app);
    fout << "Игрок получил урон в размере " << dmg << " единиц\n\n";
    if (!status) fout << "Игрок умер на координатах " << *this << "\n\n";
}

char Player::getLastPressedKey()
{
    return lastPressedKey;
}

bool Player::placeBase(int x, int y, bool player_coords, bool& do_once)
{
    if (player_coords && lastPressedKey == e)
        base.push_back(Base(x, y));

    std::sort(base.begin(), base.end());
    base.erase(std::unique(base.begin(), base.end()), base.end());

    if (do_once)
    {
        for (int i = 0; i < base.size(); i++)
            base[i].offset(lastPressedKey);
        do_once = false;
    }

    for (int i = 0; i < base.size(); i++)
        if (x == base[i].getPos_x() && y == base[i].getPos_y())
        {
            base[i].show();
            return true;
        }
    return false;
}

void Player::breakBase(int x, int y, bool player_coords)
{
    if (player_coords && (lastPressedKey == q || lastPressedKey == Q))
    {
        for (int i = 0; i < base.size(); i++)
            if (x == base[i].getPos_x() && y == base[i].getPos_y())
            {
                base.erase(base.begin() + i);
                return;
            }
    }
}

bool Player::isMoving()
{
    switch (lastPressedKey)
    {
    case w:
    case W:
    case a:
    case A:
    case s:
    case S:
    case d:
    case D:
        return true;
    default:
        return false;
    }
}