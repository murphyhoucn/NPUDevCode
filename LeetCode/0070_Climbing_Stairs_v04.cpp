#include <iostream>

// DP问题
// version3中把n的每个值都存储了，但实际上并不需要，只需要知道此时的n的前两个数值就好

class Solution
{
public:
	int climbStairs(int n)
	{
		int dp_i_1 = 1;
		int dp_i_2 = 1;

		for (int i = 2; i < n + 1; ++i)
		{
			int dp = dp_i_1 + dp_i_2;
			dp_i_2 = dp_i_1;
			dp_i_1 = dp;
		}
		return dp_i_1;
	}
};

int main()
{
	int n = 5;
	Solution solu;

	std::cout << solu.climbStairs(n);
}