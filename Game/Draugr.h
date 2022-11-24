#pragma once

#include "Undead.h"

class Draugr : public Undead
{
public:
	Draugr() : Undead(10, 5, 5, 3) 
	{
		std::ofstream fout("log.txt", std::ios::app);
		fout << this << "\n\n";
	}

	void draw()
	{
		std::cout << "\x1b[42m\x1b[30m" << level << "\x1b[0m";
	}

	friend std::ostream& operator<<(std::ostream& out, Draugr* ai)
	{
		return out << "Создан бот Draugr ID: " << ai->id;
	}
};