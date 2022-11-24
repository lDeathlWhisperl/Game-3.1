#pragma once

#include "Spirit.h"

class Mummy : public Spirit
{
public:
	Mummy() : Spirit() 
	{
		level = 1;
		std::ofstream fout("log.txt", std::ios::app);
		fout << this << "\n\n";
	}

	void draw()
	{
		std::cout << "\x1b[103m\x1b[30m" << level << "\x1b[0m";
	}

	friend std::ostream& operator<<(std::ostream& out, Mummy* ai)
	{
		return out << "Создан бот Mummy ID: " << ai->id;
	}
};