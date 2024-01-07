#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::vector <std::string> strings;
	strings.push_back("Apple");
	strings.push_back("Orange");

	// for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); it++)
    // 代码中iterator（迭代器）的类型太长了，可以直接用auto替换以获得更好的可读性：
    for (auto it = strings.begin(); it != strings.end(); it++)     
	{
		std::cout << *it << std::endl;
	}

	std::cin.get();
}