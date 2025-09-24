#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

void ForEach(std::vector<int>& values, const std::function<void(int)>& func)
{
	for (int value : values)
		func(value);
}

int main()
{
	std::vector<int> values = { 1,7,3,5,4 };
	auto it = std::find_if(values.begin(), values.end(), [](int value) {return value > 2; });
	std::cout << *it << std::endl;

	int a = 5;

	auto lambda = [=](int value) {std::cout << "Value: " << value << std::endl; };

	ForEach(values, lambda);

	std::cin.get();
}