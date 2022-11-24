#pragma once

#include "Demon.h"

class Imp : public Demon
{
public:
	Imp() : Demon(5, 1, 1, 1) 
	{
		std::ofstream fout("log.txt", std::ios::app);
		fout << this << "\n\n";
	}

	void draw()
	{
		std::cout << "\x1b[43m\x1b[30m" << level << "\x1b[0m";
	}

	friend std::ostream& operator<<(std::ostream& out, Imp* ai)
	{
		return out << "Создан бот Imp ID: " << ai->id;
	}
};