#include <iostream>
#include <string>

#include <stdlib.h>

int main()
{
    // method 1
	std::string name1 = std::string("Line1\n") + "Line2\n" + "Line3\n";
	std::cout << name1 << std::endl << std::endl;

	// method 2
	using namespace std::string_literals;
	std::string name2 = "Line1\n"s + "Line2\n" + "Line3\n";
	std::cout << name2 << std::endl << std::endl;

	// method 3
	const char* name3 = R"(Line1
Line2
Line3)";

	std::cout << name3 << std::endl << std::endl;

	// method 4
	const char* name4 = "Line1\n"
		"Line2\n"
		"Line3\n";

	std::cout << name4 << std::endl << std::endl;

	std::cin.get();
}