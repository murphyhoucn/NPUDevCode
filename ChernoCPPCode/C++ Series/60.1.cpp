#include <iostream>
#include <string>

namespace apple {
    
	void print(const std::string& text)
	{
		std::cout << text << std::endl;
	}
}

namespace orange {
    
	void print(const char* text)
	{
		std::string temp = text;
		std::reverse(temp.begin(), temp.end());
		std::cout << temp << std::endl;
	}
}

using namespace apple;
using namespace orange;

int main()
{
	print("Hello");
	std::cin.get();
}
/*
olleH
*/