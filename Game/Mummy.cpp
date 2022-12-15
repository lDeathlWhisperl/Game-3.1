#include "Mummy.h"
#include "Logging.h"

Mummy::Mummy() : Spirit()
{
	debug::log->request("Created [BOT MUMMY]     id: " + std::to_string(id) + "\n\n");
}

void Mummy::draw()
{
	std::cout << "\x1b[103m\x1b[30m" << level << "\x1b[0m";
}