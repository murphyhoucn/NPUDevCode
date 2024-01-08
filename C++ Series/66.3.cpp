#include <iostream>

int main()
{
	int a = 50; // a:32 00 00 00
	double value = *(double*)&a; // value:32 00 00 00 cc cc cc cc

	std::cout << value << std::endl; // -9.25596e+61
	std::cin.get();
}