#include <fstream>
#include <string>
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
	std::ifstream fin("settings.txt");

	std::string str;
	std::getline(fin, str, ':');

	fin >> type >> str;

	Proxy p(type);
	p.request(text);
}