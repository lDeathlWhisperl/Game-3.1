#include "Possessed.h"
#include "Logging.h"

Possessed::Possessed() : Demon(10, 4, 3, 2)
{
	debug::log->request("Created [BOT POSSESSED] id: " + std::to_string(id) + "\n\n");
}

void Possessed::draw()
{
	std::cout << level;
}