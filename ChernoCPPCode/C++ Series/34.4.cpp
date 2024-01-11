#include <iostream>
#include <string>

int main()
{
	const int MAX_NUM = 100;
	const int* const a = new int;

   	// 既不能改变指针的内容，也不能改变指针本身让它指向别处
	*a = 2;  //error!
	a = (int*)&MAX_NUM; //error!

	std::cout << *a << std::endl;
	std::cout << a << std::endl;
	std::cin.get();
}