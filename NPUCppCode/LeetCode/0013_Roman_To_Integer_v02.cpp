#include <iostream>
#include <string>
#include<map>

class Solution
{
public:
	std::map<char, int> RomanIntMap = {
		{'I', 1},
		{'V', 5},
		{'X', 10},
		{'L', 50},
		{'C', 100},
		{'D', 500},
		{'M', 1000}
	};

	int romanToInt(std::string s)
	{
		int sum = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (i + 1 < s.length() && RomanIntMap[s[i]] < RomanIntMap[s[i + 1]])
			{
				sum += RomanIntMap[s[i + 1]] - RomanIntMap[s[i]];
				i++;
			}
			else
			{
				sum += RomanIntMap[s[i]];
			}
		}
		return sum;
	}
};

int main()
{
	std::string s = "MCMXCIV";
	Solution solution;
	std::cout << solution.romanToInt(s) << std::endl;
}