#include <iostream>
#include <vector>
// 动态规划问题，DP
// 动态规划本质上就是：递归 + 记忆化
class Solution
{
public:
	int climbStairs(int n)
	{
		std::vector<int> dp(n + 1);
		dp[0] = 1;
		dp[1] = 1;

		for (int i = 2; i < n + 1; ++i)
		{
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}
};

int main()
{
	int n = 5;
	Solution solu;

	std::cout << solu.climbStairs(n);
}