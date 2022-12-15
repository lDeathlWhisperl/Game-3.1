#pragma once

#include <String>

#include "Log.h"
#include "Proxy.h"

class Adapter : public Log
{
	static int type;

	void request(std::string text);
public:
	~Adapter();
};