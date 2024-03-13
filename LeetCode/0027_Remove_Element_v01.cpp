#include <iostream>
#include <vector>

class Solution
{
public:
	int removeElement(std::vector<int>& nums, int val) //引用传递
	{
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == val)
			{
				for (int j = i + 1; j < nums.size(); j++)
				{
					nums[i] = nums[j];
				}
				nums.pop_back();
				i--;
			}
			
		}
		return nums.size();
	}
};

int main()
{
	std::vector<int> nums = { 0,1,2,2,3,0,4,2 };
	int val = 2;

	Solution solution;
	std::cout << solution.removeElement(nums, val) << ", nums = [";//引用传递

	for (int i = 0; i < nums.size(); i++)
	{
		std::cout << nums[i];
		if (i == nums.size() - 1) { std::cout << "]"; }
		else { std::cout << ", "; }
	}
}