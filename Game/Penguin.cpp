
#include <iostream>
#include "Penguin.h"

std::string Penguin::paint(int n)
{
	std::string res;
	switch (n)
	{
	case 0:
		res = "\x1b[0m";
		break;
	case 1:
		res = "\x1b[43m";
		break;
	case 2:
		res = "\x1b[107m";
		break;
	case 3:
		res = "\x1b[100m";
	}

	res += ' ';
	res += "\x1b[0m";
	return res;
}

void Penguin::draw()
{
	int peng[12][15] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,3,3,3,3,3,0,0,0},
		{0,0,0,0,0,0,3,3,3,3,3,3,3,0,0},
		{0,0,0,0,0,0,3,3,2,3,1,1,1,0,0},
		{0,0,0,0,0,0,3,3,3,3,1,1,1,1,0},
		{0,0,0,0,0,0,3,3,3,3,3,3,3,0,0},
		{0,0,0,0,0,0,3,3,3,2,2,2,2,3,0},
		{0,0,0,0,0,3,3,3,3,2,2,2,2,3,0},
		{0,0,0,0,0,3,3,3,3,2,2,2,2,3,0},
		{0,0,0,0,3,3,3,3,3,2,2,2,2,0,0},
		{0,0,0,0,0,0,1,1,1,0,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	system("cls");

	std::cout << "            quack\n";
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 15; j++)
			std::cout << paint(peng[i][j]);
		std::cout << '\n';
	}
	system("pause");
}