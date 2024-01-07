#include <iostream>
#include <string>

int main()
{
	const int MAX_NUM = 100;
	int* a = new int;
	*a = 2;
	a = (int*)&MAX_NUM;

	std::cout << *a << std::endl;
	std::cin.get();
}
// 100