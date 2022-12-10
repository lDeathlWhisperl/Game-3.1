#pragma once

#include "Log.h"
#include "Proxy.h"

#include <String>

class Adapter : public Log
{
	void request(std::string text)
	{
		Proxy p(type);
		p.request(text);
	}

	void request(unsigned int num)
	{
		Proxy p(type);
		std::string str = std::to_string(num);
		p.request(str);
	}
public:
	Adapter(int t) : Log(t) {}

	~Adapter()
	{
		if (type >= 2) Recorder::showLogInTerminal();
	}
};