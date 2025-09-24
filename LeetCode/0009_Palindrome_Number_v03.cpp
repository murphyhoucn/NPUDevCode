#include <iostream>
#include <stack>
#include <string>

class Solution
{
public:
	bool isPalindrome(int x)
	{
		bool flag = true;
		std::string x_string = std::to_string(x);
		std::stack<char> stk;
		int mid = x_string.length() / 2;
		for (int i = 0; i < mid; i++)
		{
			stk.push(x_string[i]);
		}

		for (int i = (x_string.length() % 2 == 0 ? mid : mid + 1); i < x_string.length(); i++)
		{
			if (x_string[i] != stk.top())
			{
				flag = false;
				return flag;
			}
			stk.pop();
		}
		return flag;
	}
};

int main()
{
	int x = 1234567899;
	Solution solution;
	std::cout << solution.isPalindrome(x) << std::endl;
}