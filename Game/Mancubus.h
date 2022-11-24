#pragma once

#include "Demon.h"

class Mancubus : public Demon
{
public:
	Mancubus() : Demon(15, 10, 8, 3) 
	{
		std::ofstream fout("log.txt", std::ios::app);
		fout << this << "\n\n";
	}

	void draw()
	{
		std::cout << "\x1b[41m\x1b[30m" << level << "\x1b[0m";
	}

	friend std::ostream& operator<<(std::ostream& out, Mancubus* ai)
	{
		return out << "Создан бот Mancubus ID: " << ai->id;
	}
};