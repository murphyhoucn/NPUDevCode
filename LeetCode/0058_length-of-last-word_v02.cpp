#include <iostream>
#include <string>

class Solution
{
public:
	int lengthOfLastWord(std::string s)
	{
		int n = (int)s.size();
		int cnt = 0;
		for (int i = n - 1; i > -1; --i)
		{
			if (s[i] != ' ') { ++cnt; }
			else if (cnt != 0) { break; }
		}
		return cnt;
	}
};

int main()
{
	std::string S = "a";
	Solution solu;
	std::cout << solu.lengthOfLastWord(S);
}