#include <iostream>
#include <string>

class Solution
{
public:
	int strStr(std::string haystack, std::string needle)
	{
		return (int)haystack.find(needle);
	}
};

int main()
{
	std::string Haystack = "leetcode";
	std::string Needle = "leeto";

	Solution solu;
	std::cout << solu.strStr(Haystack, Needle);
}