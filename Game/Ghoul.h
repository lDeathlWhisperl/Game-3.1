#pragma once

#include "Spirit.h"

class Ghoul : public Spirit
{
public:
	Ghoul() : Spirit(8, 7, 5, 3) 
	{
		std::ofstream fout("log.txt", std::ios::app);
		fout << this << "\n\n";
	}

	void draw()
	{
		std::cout << "\x1b[100m\x1b[30m" << level << "\x1b[0m";
	}

	friend std::ostream& operator<<(std::ostream& out, Ghoul* ai)
	{
		return out << "Создан бот Ghoul ID: " << ai->id;
	}
};