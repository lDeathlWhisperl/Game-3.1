#include <fstream>
#include "Adapter.h"

Adapter::Adapter()
{
	std::ifstream fin("Settings.txt");
	fin >> type;
}

Adapter::~Adapter()
{
	if (type != 1)
	{
		system("cls");
		Recorder::showLogInTerminal();
		std::ofstream fout("Log.txt");
		fout << "\n\n";
	}
}

void Adapter::request(std::string text)
{
	Proxy p(type);
	p.request(text);
}