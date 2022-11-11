#include "Base.h"

void Base::offset(char pressedKey)
{
	switch (pressedKey)
	{
	case 'w':
	case 'W':
		pos_y++;
		break;
	case 'a':
	case 'A':
		pos_x++;
		break;
	case 's':
	case 'S':
		pos_y--;
		break;
	case 'd':
	case 'D':
		pos_x--;
		break;
	}
}

void Base::show()
{
	std::cout << "\x1b[90m" << (unsigned char)219 << "\x1b[0m";
}

bool Base::operator<(Base b)
{
	if (pos_x < b.getPos_x())
		return true;
	if (pos_x > b.getPos_x())
		return false;
	if (pos_y < b.getPos_y())
		return true;
	return false;
}

bool Base::operator==(Base b)
{
	if (pos_x == b.getPos_x() && pos_y == b.getPos_y())
		return true;
	return false;
}