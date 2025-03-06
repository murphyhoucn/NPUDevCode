#include <iostream>
#include <fstream>
std::string ReadFileAsString(const std::string& filepath, bool& outSuccess)
{
	std::ifstream stream(filepath);
	if (stream)
	{
		std::string result;
		// read file
		stream.close();
		outSuccess = true;
		return result;
	}

	outSuccess = false;
	return std::string();
}

int main()
{
	bool fileOpenedSuccessfully;
	std::string data = ReadFileAsString("data.txt", fileOpenedSuccessfully);
	if (fileOpenedSuccessfully) {}
}