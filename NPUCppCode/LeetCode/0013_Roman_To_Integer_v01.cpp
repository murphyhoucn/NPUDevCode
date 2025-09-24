#include <iostream>
#include <string>

class Solution
{
public:	
	int romanToInt(std::string s)
	{
		int sum = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (i + 1 < s.length() && GetValue(s[i]) < GetValue(s[i + 1]))
			{
				sum += GetValue(s[i + 1]) - GetValue(s[i]);
				i++;
			}
			else
			{
				sum += GetValue(s[i]);
			}
		}
		return sum;
	}

private:
	int GetValue(char ch)
	{
		int value = 0;
		switch (ch)
		{
		case 'I': value = 1; break;
		case 'V': value = 5; break;
		case 'X': value = 10; break;
		case 'L': value = 50; break;
		case 'C': value = 100; break;
		case 'D': value = 500; break;
		case 'M': value = 1000; break;
		default:
			break;
		}
		return value;
	}
};

int main()
{
	std::string s = "MCMXCIV";
	Solution solution;
	std::cout << solution.romanToInt(s) << std::endl;
}