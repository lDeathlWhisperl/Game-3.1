#pragma once

#include "Recorder.h"

class Proxy
{
	int type;

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
		Recorder::withoutLog();
	}
public:
	Proxy(int t) : type(t) {}

	void request(std::string text)
	{
		switch (type)
		{
		case 1:
			logToFile(text);
			break;
		case 2:
			logToTerminal(text);
			break;
		default:
			withoutLog();
		}
	}
};