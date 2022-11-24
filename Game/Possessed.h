#pragma once

#include "Demon.h"

class Possessed : public Demon
{
public:
	Possessed() : Demon(10, 4, 3, 2) 
	{
		std::ofstream fout("log.txt", std::ios::app);
		fout << this << "\n\n";
	}

	void draw()
	{
		std::cout << level;
	}

	friend std::ostream& operator<<(std::ostream& out, Possessed* ai)
	{
		return out << "Создан бот Possessed ID: " << ai->id;
	}
};