#include "Player.h"

void Player::controller()
{
    char ch = '\0';
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

        break;
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

char Player::getLastPressedKey()
{
    return lastPressedKey;
}

bool Player::placeBlock(std::vector<Block>& blocks, int x, int y, bool player_coords, bool& do_once)
{
    if (player_coords && lastPressedKey == 'e')
    {
        blocks.push_back(Block(x, y));
    }

    if (do_once && !blocks.empty())
    {
        for (int i = 0; i < blocks.size(); i++)
            blocks[i].offset(lastPressedKey);
        do_once = false;
    }

    if (!blocks.empty())
    {
        for (int i = 0; i < blocks.size(); i++)
            if (x == blocks[i].getPos_x() && y == blocks[i].getPos_y())
            {
                blocks[i].show();
                return true;
                break;
            }
    }
    return false;
}