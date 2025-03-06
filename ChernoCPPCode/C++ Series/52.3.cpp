#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int> returnWithTuple()
{
	return std::make_tuple("Hello", 42);
}

std::pair<std::string, int> returnWithPair()
{
	return std::make_pair("Hello", 42);
}

int main()
{
	std::tuple<std::string, int> tupleResult = returnWithTuple();
	std::cout << std::get<0>(tupleResult) << ", " << std::get<1>(tupleResult) << std::endl;

	std::pair<std::string, int> pairResult = returnWithPair();
	std::cout << pairResult.first << ", " << pairResult.second << std::endl;

	return 0;
}