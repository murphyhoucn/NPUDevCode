#include <iostream>
#include <string>

void PrintString(std::string& onename) // 传引用的话情况就会不一样了
{
	onename += " hello";
	std::cout << onename << std::endl;
}

int main()
{
	std::string name = "Cherno";
	PrintString(name);  // Cherno hello
	std::cout << name << std::endl; // Cherno hello

	std::cin.get();
}