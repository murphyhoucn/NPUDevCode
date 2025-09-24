#include <iostream>
#include <string>

void returnWithReference(std::string& str, int& num)
{
	str = "Hello";
	num = 42;
}


int main()
{
	std::string str;
	int num;
	returnWithReference(str, num);

	std::cout << str << ", " << num << std::endl;

	return 0;
}