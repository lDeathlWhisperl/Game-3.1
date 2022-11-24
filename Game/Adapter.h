#pragma once

#include "Recorder.h"

class Adapter
{
	std::string txt, filename;
	int req;

	void logToFile(std::string file, std::string text)
	{
		Recorder::writeToFile(file, text);
	}

	void logToTerminal(std::string text)
	{
		Recorder::writeToTerminal(text);
	}

	void withoutLog()
	{
		
	}
public:
	Adapter() : req(0) {}
	Adapter(std::string text) : txt(text), req(1) {}
	Adapter(std::string file, std::string text) : filename(file), txt(text), req(2) {}

	void request()
	{
		switch (req)
		{
		case 0:
			withoutLog();
			break;
		case 1:
			logToTerminal(txt);
			break;
		case 2:
			logToFile(filename, txt);
			break;
		}
	}
};