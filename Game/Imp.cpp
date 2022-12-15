#include "Imp.h"
#include "Logging.h"

Imp::Imp() : Demon(5, 1, 1, 1)
{
	debug::log->request("Created [BOT IMP]       id: " + std::to_string(id) + "\n\n");
}

void Imp::draw()
{
	std::cout << "\x1b[43m\x1b[30m" << level << "\x1b[0m";
}