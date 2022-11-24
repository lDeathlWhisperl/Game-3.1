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
		fout << text << "\n\n";
	}

	static void writeToTerminal(std::string text)
	{
		terminal += text;
		terminal += "\n\n";
	}

	static void showLogInTerminal()
	{
		std::cout << terminal;
	}
};

std::string Recorder::terminal = "";