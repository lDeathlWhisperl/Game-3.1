#include "Zombie.h"
#include "Logging.h"

Zombie::Zombie() : Undead(5, 1, 2, 2)
{
	debug::log->request("Created [BOT ZOMBIE]    id: " + std::to_string(id) + "\n\n");
}

void Zombie::draw()
{
	std::cout << "\x1b[102m\x1b[30m" << level << "\x1b[0m";
}