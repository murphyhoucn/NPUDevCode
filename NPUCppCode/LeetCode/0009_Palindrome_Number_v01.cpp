#include <iostream>
#include <string>

class Solution
{
public:
	bool isPalindrome(int x)
	{

		std::string x_string1 = std::to_string(x);
		std::string x_string2 = x_string1;

		std::reverse(x_string1.begin(), x_string1.end());

		bool flag = x_string1 == x_string2;
		return flag;
	}
};
int main()
{
	int x = -1234567899;
	Solution solution;
	std::cout << solution.isPalindrome(x) << std::endl;
}