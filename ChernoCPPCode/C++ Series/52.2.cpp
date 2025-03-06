#include <iostream>
#include <string>
#include <array>
#include <vector>

std::array<int, 2> returnWithArray()
{
	std::array<int, 2> result;

	result[0] = 42;
	result[1] = 56;

	return result;
}

std::vector<int> returnWithVector()
{
	std::vector<int> result;

	result.push_back(42);
	result.push_back(56);

	return result;
}

int main()
{
	std::array<int, 2> arrResult = returnWithArray();
	std::cout << arrResult[0] << ", " << arrResult[1] << std::endl;

	std::vector<int> vecResult = returnWithVector();
	std::cout << vecResult[0] << ", " << vecResult[1] << std::endl;

	return 0;
}