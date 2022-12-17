#include <iostream>
#include "Game.h"

void colors()
{
	for (int i = 1; i < 110; i++)
		std::cout << "\x1b[" << i << "m" << (char)219 << ' ' << i << "\x1b[0m\n";
}

int main()
{
    Game::init(); 
    return 0;
}