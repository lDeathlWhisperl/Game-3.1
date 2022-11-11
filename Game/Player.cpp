#include "Player.h"
#include <algorithm>

bool collision(int num)
{
    switch (num)
    {
    case 0:
    case 2:
    case 3:
        return true;
    default:
        return false;
    }
}

Player::Player()
{
    character = '^';
}

void Player::controller(int coll)
{
    char ch = '\0';
    if (_kbhit())
        ch = _getch();

    switch (ch)
    {
    case w:
    case W:
        if (!collision(coll))
            pos_y--;
    case ARROW_UP:
        character = '^';
        break;
    case a:
    case A:
        if (!collision(coll))
            pos_x--;
    case ARROW_LEFT:
        character = '<';
        break;
    case s:
    case S:
        if (!collision(coll))
            pos_y++;
    case ARROW_DOWN:
        character = 'V';
        break;
    case d:
    case D:
        if (!collision(coll))
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

char Player::showPlayer()
{
    return character;
}

void Player::getDamage(int dmg)
{
    Character::getDamage(dmg);
    /* fixing
    switch (character)
    {
    case '^':
        pos_y++;
        break;
    case '<':
        pos_x++;
        break;
    case 'V':
        pos_y--;
        break;
    case '>':
        pos_x--;
        break;
    }
    */
}

char Player::getLastPressedKey()
{
    return lastPressedKey;
}

bool Player::placeBase(int x, int y, bool player_coords, bool& do_once)
{
    if (player_coords && (lastPressedKey == e || lastPressedKey == E))
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