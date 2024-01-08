#include <iostream>

int main()
{
	// 隐式类型转换，很容易做到且没有数据丢失
	int a1 = 5;
	double b1 = a1;
	std::cout << a1 << ", " << b1 << std::endl;

	// 隐式类型转换，因为不需要具体说明要把这个类型转换成哪个类型
	double a2 = 5.3;
	int b2 = a2;
	std::cout << a2 << ", " << b2 << std::endl;

	// 显示类型转换
	double a3 = 5.3;
	int b3 = (int)a3;
	std::cout << a3 << ", " << b3 << std::endl;

	std::cin.get();
}
/*
5, 5
5.3, 5
5.3, 5
*/