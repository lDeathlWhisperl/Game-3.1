#include <fstream>
#include "Adapter.h"

int Adapter::type;

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
	std::ifstream fin("Settings.txt");
	fin >> type;
	Proxy p(type);
	p.request(text);
}