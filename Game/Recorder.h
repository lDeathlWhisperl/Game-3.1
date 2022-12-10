#pragma once

#include <fstream>
#include <iostream>

class Recorder
{
	static std::string terminal;
public:
	Recorder() {};

	~Recorder() {};

	static void writeToFile(std::string text)
	{
		std::ofstream fout("log.txt");

		terminal += text;

		fout << terminal;
	}

	static void writeToTerminal(std::string text)
	{
		terminal += text;
	}

	static void withoutLog()
	{
		terminal = "Loging has not been enabled\n\n";
	}

	static void showLogInTerminal()
	{
		std::cout << terminal;
	}
};

std::string Recorder::terminal = "";