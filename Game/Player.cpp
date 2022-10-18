#include "Player.h"

void Player::controller()
{
    char ch = _getch();

    switch (ch)
    {
    case 'w':
        character = '^';
        pos_y--;
        break;
    case 'a':
        character = '<';
        pos_x--;
        break;
    case 's':
        character = 'V';
        pos_y++;
        break;
    case 'd':
        character = '>';
        pos_x++;
        break;
    }
}

char Player::showPlayer()
{
    return character;
}