#include <iostream>
#include <cmath>
#include <vector>
#include "World.h"

//32 - лес
//92 - поляна

//34 - темная вода
//94 - светлая вода
//36 - ручей

//93 - песок
//90 - камень
//33 - мост

int random(int min, int max)
{
	return min + rand() % (max - min + 1);
}

std::vector<int> World::diamond(int sq_a, int sq_b, int sq_c, int sq_d, int length)
{
	std::vector<int> res;
	int spec = 1;

	int A = sq_a,
		B = sq_b,
		C = sq_c,
		D = sq_d;

	int mid = A + ((B - A) / 2 * (length + 1));

	if(random(0, 1))
		spec = (vertexes[A] + vertexes[B] + vertexes[C] + vertexes[D]) / 4 + random(0, 1);
	else
		spec = (vertexes[A] + vertexes[B] + vertexes[C] + vertexes[D]) / 4 - random(0, 1);

	vertexes[mid] = (vertexes[A] + vertexes[B] + vertexes[C] + vertexes[D]) / 4 + spec;
	int h_mid = vertexes[mid];
	spec /= 2;

	int left   = mid - (B - A) / 2,
		top    = A   + (B - A) / 2,
		right  = mid + (B - A) / 2,
		bottom = C   + (B - A) / 2;

	if ((B - A) % 2 != 0)
		right++;

	if(vertexes[left] == 0)
		vertexes[left] = (A + C + h_mid) / 3 + random(0, spec);
	if (vertexes[top] == 0)
		vertexes[top] = (A + B + h_mid) / 3 + random(0, spec);
	if (vertexes[right] == 0)
		vertexes[right] = (B + D + h_mid) / 3 + random(0, spec);
	if (vertexes[bottom] == 0)
		vertexes[bottom] = (C + D + h_mid) / 3 + random(0, spec);

	res.push_back(A);      //0
	res.push_back(B);      //1
	res.push_back(C);      //2
	res.push_back(D);      //3
	res.push_back(mid);    //4
	res.push_back(left);   //5
	res.push_back(top);    //6
	res.push_back(right);  //7
	res.push_back(bottom); //8

	return res;
}

void World::landscape(int length, int width)
{
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < length; x++)
			vertexes.push_back(0);
	}
}

void World::generator(int length, int width)
{
	landscape(length, width);

	int sq_a = 0,
		sq_b = length - 1,
		sq_c = vertexes.size() - length,
		sq_d = length * length - 1;

	srand(static_cast<unsigned int>(time(0)));

	vertexes[sq_a] = random(0, 1);
	vertexes[sq_b] = random(0, 1);
	vertexes[sq_c] = random(0, 1);
	vertexes[sq_d] = random(0, 1);

	std::vector<int> A;
	std::vector<int> B;
	std::vector<int> C;
	std::vector<int> D;
	std::vector<int> A_0;
	std::vector<int> B_0;
	std::vector<int> C_0;
	std::vector<int> D_0;

	for (int i = 0; i < vertexes.size() / 4 * vertexes.size(); i++)
	{
		A.push_back(0);
		B.push_back(0);
		C.push_back(0);
		D.push_back(0);
		A_0.push_back(0);
		B_0.push_back(0);
		C_0.push_back(0);
		D_0.push_back(0);
	}

	A[1] = sq_a;
	B[1] = sq_b;
	C[1] = sq_c;
	D[1] = sq_d;

	//a      - 0
	//b      - 1
	//c      - 2
	//b      - 3
	//mid    - 4
	//left   - 5
	//top    - 6
	//right  - 7
	//bottom - 8

	//std::vector<int> dots = diamond(sq_a, sq_b, sq_c, sq_d, length);

	//dots = diamond(dots[5], dots[4], dots[2], dots[8], length);

	//dots = diamond(dots[5], dots[4], dots[2], dots[8], length);
	
	int counter = 1;
	int counter_0 = 1;
	for (int i = 1; i <= log2(length); i++)
	{
		for (int j = 1; j <= counter; j++)
		{
			std::vector<int> dots = diamond(A[j], B[j], C[j], D[j], length);
			
			A_0[counter_0] = dots[0]; //A
			B_0[counter_0] = dots[6]; //top
		    C_0[counter_0] = dots[5]; //left
			D_0[counter_0] = dots[4]; //mid
			counter_0++;
			
			
			A_0[counter_0] = dots[5]; //left
			B_0[counter_0] = dots[4]; //mid
			C_0[counter_0] = dots[2]; //C
			D_0[counter_0] = dots[8]; //bottom
			counter_0++;
			
			
			A_0[counter_0] = dots[6]; //top
			B_0[counter_0] = dots[1]; //B
			C_0[counter_0] = dots[4]; //mid
			D_0[counter_0] = dots[7]; //right
			counter_0++;
			
			
			A_0[counter_0] = dots[4]; //mid
			B_0[counter_0] = dots[7]; //right
			C_0[counter_0] = dots[8]; //bottom
			D_0[counter_0] = dots[3]; //D
			counter_0++;
			
		}

		A = A_0;
		B = B_0;
		C = C_0;
		D = D_0;
		counter_0 = 1;
		counter *= 4;
	}
	
		
}

std::string World::paint(int high)
{
	std::string res;

	

	res += tile;
	res += "\x1b[0m";
	return res;
}

void World::draw(int length, int width)
{
	for (int i = 1; i < vertexes.size()+1; i++)
	{
		std::cout << paint(vertexes[i - 1]);// << ' ';

		if (!(i % length))
			std::cout << '\n';
	}
		
}

void World::clean()
{
	std::cout << "\x1b[2J";
}