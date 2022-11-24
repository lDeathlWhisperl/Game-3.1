#pragma once

#include "Undead.h"

class Zombie : public Undead
{
public:
	Zombie() : Undead(5, 1, 2, 2) 
	{
		std::ofstream fout("log.txt", std::ios::app);
		fout << this << "\n\n";
	}

	void draw()
	{
		std::cout << "\x1b[102m\x1b[30m" << level << "\x1b[0m";
	}

	friend std::ostream& operator<<(std::ostream& out, Zombie* ai)
	{
		return out << "Создан бот Zombie ID: " << ai->id;
	}
};