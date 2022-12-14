#pragma once

#include "Log.h"
#include "Proxy.h"

#include <String>

class Adapter : public Log
{
	int type;

	void request(std::string text)
	{
		Proxy p(type);
		p.request(text);
	}
public:
	Adapter() 
	{
		std::ifstream fin("Settings.txt");
		fin >> type;
	}

	~Adapter()
	{
		if (type != 1) 
		{
			system("cls");
			Recorder::showLogInTerminal();
			std::ofstream fout("Log.txt");
			fout << "\n\n";
		}
	}
};