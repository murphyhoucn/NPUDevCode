#include <iostream>
#include <string>
#include <algorithm>

class Solution
{
public:
	int lengthOfLastWord(std::string s)
	{
		reverse(s.begin(), s.end());
		// std::cout << s << std::endl;

		int index = 0;
		while (s[index] == ' ')
		{
			index++;
		}
		int start = index;
		while (s[index] != ' '&& s[index] != '\0')
		{
			index++;
		}
		return index - start;
	}
};

int main()
{
	std::string S = "a";
	Solution solu;
	std::cout << solu.lengthOfLastWord(S);
}