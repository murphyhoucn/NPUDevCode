#include <iostream>
#include <string>

class Solution
{
public:
	bool isPalindrome(int x)
	{
		bool flag = false;
		int x_t = x;
		if (x < 0)
		{
			flag = false;
		}
		else
		{
			long long int x_reverse = 0;
			while (x > 0)
			{
				x_reverse = x_reverse * 10 + x % 10;
				x /= 10;
			}

			//std::cout << "x = " << x << std::endl;
			//std::cout << "x_reverse = " << x_reverse << std::endl;

			if (x_reverse == x_t)
			{
				flag = true;
			}
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