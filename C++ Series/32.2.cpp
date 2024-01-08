#include <iostream>
#include <string>

void PrintString(std::string onename)
{
	onename += " hello";
	std::cout << onename << std::endl;
}

int main()
{
	std::string name = "Cherno";
	PrintString(name);  // Cherno hello
	std::cout << name << std::endl; // Cherno

	std::cin.get();
}