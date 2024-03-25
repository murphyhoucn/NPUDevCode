#include <iostream>

// 递归法
// 存储已经计算过的
// accepted

class Solution
{
public:
	int climbStairs(int n)
	{
		int* memory = new int[n + 1];
		int result = calculate(n, memory);
		delete[] memory;
		return result;
	}
	
	int calculate(int n, int* memory)
	{
		if (n == 1) return 1;
		if (n == 2) return 2;
		if (memory[n] > 0) return memory[n];

		memory[n] = calculate(n - 1, memory) + calculate(n - 2, memory);
		return memory[n];
	}
};
int main()
{
	int n = 5;
	Solution solu;
	
	std::cout << solu.climbStairs(n);
}