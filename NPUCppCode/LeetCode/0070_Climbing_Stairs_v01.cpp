#include <iostream>

// 方法：递归方法
// 结果：leetcode不通过：时间超时
// 分析：当n很大的时候，递归好多次，每次递归都会有重复运算
class Solution
{
public:
	int climbStairs(int n)
	{
		if (n == 1) return 1;
		if (n == 2) return 2;

		return climbStairs(n - 1) + climbStairs(n - 2);
	}
};
int main()
{
	int n = 5;
	Solution solu;

	std::cout << solu.climbStairs(n);
}