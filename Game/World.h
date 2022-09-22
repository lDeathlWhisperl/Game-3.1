#pragma once

#include <iostream>
#include <cmath>

//32 - лес
//92 - поляна

//34 - темная вода
//94 - светлая вода
//36 - ручей

//93 - песок
//90 - камень
//33 - мост

class World
{
private:
	char tile = 219;

	double noise(int x, int y, int freq, int high)
	{
		const double PI = 3.1415926535;
		double width = cos(freq * x * PI / 180);
		double length = cos(freq * y * PI / 180);
		return width * length * high;
	}

	int landscape(int x, int y)
	{
		double noise_1 = noise(x, y, 10, 4);
		double noise_2 = noise(x, y, 5, 7);
		double noise_3 = noise(x, y, 12, 6);

		return static_cast<int>(round(noise_1 + noise_2 + noise_3));
	}

	std::string paint(int high)
	{
		std::string res;
		
		if (high <= -11)
			res = "\x1b[32m"; // deep water layer
		if(high >= 2)
			res = "\x1b[92m";

		switch (high)
		{
		case -10:
			res = "\x1b[32m"; // shallow water layer
			break;

		case -9:
			res = "\x1b[32m"; // sand layer
			break;

		case -8:
		case -7:
		case -6:
		case -5:
			res = "\x1b[32m"; // forest layer
			break;
		case -4:
		case -3:
		case -2:
		case -1:
			res = "\x1b[92m"; // field layer
			break;

		case 0:
		case 1:
			res = "\x1b[36m"; // river layer
			break;

		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			res = "\x1b[32m"; // forest layer
			break;

		case 999:
			res = "\x1b[90m"; // fort layer
		}

		res += tile;
		res += "\x1b[0m";
		return res;
	}

public:
	void draw(int length, int width)
	{
		for (int y = 1; y < width; y++)
		{
			for (int x = 1; x < length; x++)
			{
				if (x <= 4 && y <= 3)
					std::cout << paint(999);
				else
					std::cout << paint(landscape(x, y));// << ' ';
			}
			std::cout << '\n';
		}
			
	}

	void clean()
	{
		std::cout << "\x1b[2J";
	}
};