#include <iostream>
#include <string>

int main()
{
	const int MAX_NUM = 100;
	const int* a = new int;  
    // int const* a = new int; // 两种写法相同
	*a = 2; // error! const使你不能修改a指针指向的内容
	a = (int*)&MAX_NUM;

	std::cout << *a << std::endl;
	std::cin.get();
}