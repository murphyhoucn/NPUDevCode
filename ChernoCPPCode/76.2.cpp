#include <iostream>
#include <fstream>
#include <optional>

std::optional <std::string> ReadFileAsString(const std::string& filepath)
{
	std::ifstream stream(filepath);
	if (stream)
	{
		std::string result;
		// Read file
		stream.close();
		return result;
	}
	return {};

}

int main()
{
	std::optional<std::string> data = ReadFileAsString("data.txt"); // 可以auto
	if (data)// 本来可以写data.has_value()，但是data对象有一个bool运算符，所以这样写更简洁
	{
		std::cout << "file read successfully\n";
	}
	else
	{
		std::cout << "file could not read\n";
	}
	std::cin.get();
}