#pragma once

#include "Spirit.h"

class Gin : public Spirit
{
public:
	Gin() : Spirit(5, 1, 4, 2) 
	{
		std::ofstream fout("log.txt", std::ios::app);
		fout << this << "\n\n";
	}

	void draw()
	{
		std::cout << "\x1b[106m\x1b[30m" << level << "\x1b[0m";
	}

	friend std::ostream& operator<<(std::ostream& out, Gin* ai)
	{
		return out << "Создан бот Gin ID: " << ai->id;
	}
};