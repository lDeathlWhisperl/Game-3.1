#pragma once

class Log
{
public:
	virtual ~Log() {}
	virtual void request() = 0;
};