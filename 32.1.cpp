#include <iostream>

int main()
{
	// 用pointer定义一个字符串，使用const意味着这个字符串不能修改
	const char* name = "Cherno";
	// char* name = "Cherno"; // 不要用这种写法，
	std::cout << name << std::endl;

	// char* name1 = "Cherno"; // 不要用这种写法，
	// std::cout << name1 << std::endl;

	// 用array定义一个字符串，可以修改
	// char name2[6] = { 'C', 'h', 'e', 'r', 'n','o' }; // error!
	char name2[7] = { 'C', 'h', 'e', 'r', 'n','o', '\0' }; // '\0': null termination character

	name2[0] = 'A';
	std::cout << name2 << std::endl;

	std::cin.get();
}