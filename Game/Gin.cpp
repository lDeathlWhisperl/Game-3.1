#include "Gin.h"
#include "Logging.h"

Gin::Gin() : Spirit(5, 1, 4, 2)
{
	debug::log->request("Created [BOT GIN]       id: " + std::to_string(id) + "\n\n");
}

void Gin::draw()
{
	std::cout << "\x1b[106m\x1b[30m" << level << "\x1b[0m";
}