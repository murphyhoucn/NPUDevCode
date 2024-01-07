#include <iostream>
#include <string>

int main()
{
	const int MAX_NUM = 100;
	int* const a = new int;
	*a = 2; 
	a = (int*)&MAX_NUM; // error！可以改变指针指向的内容，但是不能把指针自身重新赋值，让它指向其它东西

	std::cout << *a << std::endl;
	std::cin.get();
}