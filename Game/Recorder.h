#pragma once

#include <iostream>

class Recorder
{
	static std::string terminal;
public:
	Recorder() {};

	~Recorder() {};

	static void writeToFile(std::string);

	static void writeToTerminal(std::string);

	static void withoutLog();

	static void showLogInTerminal();
};