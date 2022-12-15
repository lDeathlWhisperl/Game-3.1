#include "Ghoul.h"
#include "Logging.h"

Ghoul::Ghoul() : Spirit(8, 7, 5, 3)
{
	debug::log->request("Created [BOT GHOUL]     id: " + std::to_string(id) + "\n\n");
}
void Ghoul::draw()
{
	std::cout << "\x1b[100m\x1b[30m" << level << "\x1b[0m";
}