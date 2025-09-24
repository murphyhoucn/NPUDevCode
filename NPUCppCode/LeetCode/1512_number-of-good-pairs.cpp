#include <iostream>
#include <vector>

class Solution
{
public:
    int numIdenticalPairs(std::vector<int> &nums)
    {
        int count = 0;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] == nums[j])
                    count++;
            }
        }

        return count;
    }
};

int main()
{
    std::vector<int> nums = {1, 2, 3, 1, 1, 3};
    Solution solu;
    std::cout << solu.numIdenticalPairs(nums) << std::endl;

    return 0;
}

/*
暴力统计，嵌套两个for循环
时间复杂度：O(n^2)
空间复杂度：O(1)
*/