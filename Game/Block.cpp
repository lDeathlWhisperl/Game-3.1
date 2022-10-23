#include "Block.h"

Block::Block(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

void Block::offset(char pressedKey)
{
	switch (pressedKey)
	{
	case 'w':
		pos_y++;
		break;
	case 'a':
		pos_x++;
		break;
	case 's':
		pos_y--;
		break;
	case 'd':
		pos_x--;
		break;
	}
}

void Block::show()
{
	std::cout << "\x1b[90m" << (unsigned char)219 << "\x1b[0m";
}