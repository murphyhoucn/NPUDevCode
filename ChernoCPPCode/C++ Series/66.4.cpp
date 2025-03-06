#include <iostream>

struct Entity
{
	int x, y;
};

int main()
{
	Entity e = { 5,8 };

	int* position = (int*)&e;
	std::cout << position[0] << ", " << position[1] << std::endl; // 5, 8

	int y = *(int*)((char*)&e + 4);
	std::cout << y << std::endl; // 8

	std::cin.get();
}