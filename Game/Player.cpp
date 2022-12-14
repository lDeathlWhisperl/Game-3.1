#include "Player.h"
#include "Loging.h"

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
    debug::log->request("Creating the player\n\n");
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
    
    debug::log->request("The player has taken " + std::to_string(dmg) + " points of damage\n\n");
    if (!status)
        debug::log->request("The player died on x: " + std::to_string(pos_x) + " y: " + std::to_string(pos_y) + " coordinates\n\n");
}

char Player::getLastPressedKey()
{
    return lastPressedKey;
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