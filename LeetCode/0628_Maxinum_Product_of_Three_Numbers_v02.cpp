#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
	int maximumProduct(std::vector<int>& nums)
	{
		std::sort(nums.begin(), nums.end());
		int max1 = nums[0] * nums[1] * nums[nums.size() - 1];
		int max2 = nums[nums.size() - 3] * nums[nums.size() - 2] * nums[nums.size() - 1];
		return max1 > max2 ? max1 : max2;
	}
};

int main()
{
	std::vector<int> nums = { 1,2,3};
	// std::vector<int> nums = { 1,2,3,4 };
	// std::vector<int> nums = { -1,-2,-3 };

	Solution solution;
	std::cout << solution.maximumProduct(nums) << std::endl;

}