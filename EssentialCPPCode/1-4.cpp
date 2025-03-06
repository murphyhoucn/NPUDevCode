#include <iostream>
#include <string>

int main()
{
	std::string UserFirstName;
	std::string UserLastName;

	std::cout << "Please enter your name:"; 
	std::cin >> UserFirstName;
	std::cin >> UserLastName;

	std::cout << "\n"
		<< "Hello, "
		<< UserFirstName
		<< " "
		<< UserLastName
		<< "... and goodbye! \n";

	return 0;
}