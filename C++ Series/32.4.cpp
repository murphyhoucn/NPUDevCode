#include <iostream>
#include <string>

void PrintString(const std::string& onename) // 如果有const的话，又是另外一种情况，这时候，onename即name的值不能改变
{
	// onename += " hello";
	std::cout << onename << std::endl;
}

int main()
{
	std::string name = "Cherno";
	PrintString(name);  // Cherno
	std::cout << name << std::endl; // Cherno

	std::cin.get();
}