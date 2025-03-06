#include <iostream>
#include <string>

int main()
{
	std::string user_name;
	std::cout << "Please enter your name:";
	std::cin >> user_name;
	std::cout << "\n"
		<< "Hello, "
		<< user_name
		<< "... and goodbye! \n";

	return 0;
}