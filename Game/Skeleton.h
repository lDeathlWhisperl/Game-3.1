#pragma once

#include "Undead.h"

class Skeleton : public Undead
{
public:
	Skeleton() : Undead() 
	{
		std::ofstream fout("log.txt", std::ios::app);
		fout << this << "\n\n";
	}

	void draw()
	{
		std::cout << "\x1b[47m\x1b[30m" << level <<"\x1b[0m";
	}

	friend std::ostream& operator<<(std::ostream& out, Skeleton *ai)
	{
		return out << "Создан бот Skeleton ID: " << ai->id;
	}
};