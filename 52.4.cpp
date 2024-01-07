#include <iostream>
#include <string>

struct Result
{
	std::string str;
	int num;
};

Result returnWithStruct()
{
	Result result;
	result.str = "Hello";
	result.num = 42;

	return result;
}

int main()
{
	Result structResult = returnWithStruct();
	std::cout << structResult.str << ", " << structResult.num << std::endl;

	return 0;
}