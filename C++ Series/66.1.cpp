#include <iostream>

int main()
{
	int a = 50; // a:32 00 00 00 (十六进制)
	double value = a; // value:00 00 00 00 00 00 49 40 (十六进制)  //隐式类型转换

	std::cout << value << std::endl;  // 50
	std::cin.get();
}