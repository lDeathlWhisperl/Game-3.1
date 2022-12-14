#include <fstream>
#include "Recorder.h"


std::string Recorder::terminal = "";

void Recorder::writeToFile(std::string text)
{
	std::ofstream fout("log.txt");

	terminal += text;

	fout << terminal;
}

void Recorder::writeToTerminal(std::string text)
{
	terminal += text;
}

void Recorder::withoutLog()
{
	terminal = "Loging has not been enabled\n\n";
}

void Recorder::showLogInTerminal()
{
	std::cout << terminal;
}