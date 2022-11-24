#pragma once

#include "Recorder.h"

class Proxy
{
	void logToFile(std::string text)
	{
		Recorder::writeToFile(text);
	}

	void logToTerminal(std::string text)
	{
		Recorder::writeToTerminal(text);
	}

	void withoutLog()
	{
		
	}
public:
	Proxy() {}

	void request()
	{

	}
};