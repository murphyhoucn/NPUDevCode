#include <iostream>
#include <vector>

class Solution
{
public:
	std::vector<int> twoSum(std::vector<int>&nums, int target)
	{
		std::vector<int> Ans;
		// cout << "vector size:" << nums.size() << std::endl;
		
		for (int i = 0; i < nums.size() - 1; i++)
		{
			for (int j = i + 1; j < nums.size(); j++)
			{
				if (nums[i] + nums[j] == target)
				{
					Ans.push_back(i);
					Ans.push_back(j);
					return Ans;
				}
			}
		}
		return Ans;
	}
};

int main()
{
	Solution solution;
	std::vector<int> nums = { 3,3 };
	int target = 6;

	std::cout << '[' << solution.twoSum(nums, target)[0] << ',' << solution.twoSum(nums, target)[1] << "]" << std::endl;
}