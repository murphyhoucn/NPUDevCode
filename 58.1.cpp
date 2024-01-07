#include <iostream>

void HelloWorld()
{
	std::cout << "Hello world" << std::endl;
}
int main()
{
	auto fun1 = HelloWorld;
	fun1();

	void(*fun2)() = HelloWorld;
	fun2();

	std::cin.get();
}