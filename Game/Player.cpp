#include "Player.h"

void Player::controller()
{
    char ch = '0';
    if(_kbhit())
        ch = _getch();

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
    case 'q':

        break;
    case 'e':
        //std::cout << "\x1b[90m" << (unsigned char)219 << "\x1b[0m";
        break;
    }
}

char Player::showPlayer()
{
    return character;
}

void Player::getDamage(int dmg)
{
    Actor::getDamage(dmg);

    switch (character)
    {
    case '^':
        pos_y += 1;
        break;
    case '<':
        pos_x += 1;
        break;
    case 'V':
        pos_y -= 1;
        break;
    case '>':
        pos_x -= 1;
        break;
    }
}