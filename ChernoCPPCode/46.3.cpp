#include <iostream>
#include <string>

struct Vector3
{
	float x, y, z;
};

int main()
{
	int offsetx = (int)&((Vector3*)nullptr)->x;
	std::cout << offsetx << std::endl;

	int offsety = (int)&((Vector3*)nullptr)->y;
	std::cout << offsety << std::endl;

	int offsetz = (int)&((Vector3*)nullptr)->z;
	std::cout << offsetz << std::endl;

	std::cin.get();
}

/*
0
4
8
*/