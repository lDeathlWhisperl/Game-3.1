#pragma once

class Log
{
protected:
	int type;
public:
	Log(int t) : type(t) {}
	virtual ~Log() {}
	virtual void request(std::string) = 0;
	virtual void request(unsigned int) = 0;
};