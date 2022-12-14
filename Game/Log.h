#pragma once

class Log
{
public:
	Log() {}
	virtual ~Log() {}
	virtual void request(std::string) = 0;
};