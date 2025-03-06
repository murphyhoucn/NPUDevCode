#include <iostream>
#include <vector>

class Solution {
public:
	int searchInsert(std::vector<int>& nums, int target) 
	{
		int NumsLeft = 0;
		int NumsRight = (int)nums.size() - 1;
		while (NumsLeft <= NumsRight)
		{
			int NumsMid = NumsLeft + (NumsRight - NumsLeft) / 2;

			if (nums[NumsMid] == target) { return NumsMid; }
			else if (nums[NumsMid] > target) { NumsRight = NumsMid - 1; }
			else { NumsLeft = NumsMid + 1; }
		}
		return NumsLeft;
	}
};

int main()
{
	std::vector<int> Nums = { 1,2,3,5,7 };
	int target = 5;

	Solution solu;
	std::cout << solu.searchInsert(Nums, target);
}