#include <iostream>
#include <vector>

// 测试用例通过
// 提交代码的时候测试的一个非常大的数组！！然后“超出时间限制”了！
class Solution
{
public:
	int maximumProduct(std::vector<int>& nums)
	{
		int NumsSize = nums.size();
		int Product = nums[0] * nums[1] * nums[2];
		for (int i = 0; i < NumsSize - 2; i++)
		{
			for (int j = i + 1; j < NumsSize - 1; j++)
			{
				for (int k = j + 1; k < NumsSize; k++)
				{
					int NewProduct = nums[i] * nums[j] * nums[k];
					Product = NewProduct > Product ? NewProduct : Product;
				}
			}
		}
		return Product;
	}
};

int main()
{
	// std::vector<int> nums = { 1,2,3};
	// std::vector<int> nums = { 1,2,3,4 };
	std::vector<int> nums = { -1,-2,-3 };

	Solution solution;
	std::cout << solution.maximumProduct(nums) << std::endl;

}