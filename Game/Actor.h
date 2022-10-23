#pragma once

class Actor
{
protected:
	int pos_x = 0;
	int pos_y = 0;

public:
	int getPos_x()
	{
		return pos_x;
	}

	int getPos_y()
	{
		return pos_y;
	}

	void setPos_x(int x)
	{
		pos_x = x;
	}

	void setPos_y(int y)
	{
		pos_y = y;
	}
};