#include <iostream>
#include <vector>

class Solution
{
public:
    int countPairs(std::vector<int> &nums, int target)
    {
        int count = 0;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] + nums[j] < target)
                    count++;
            }
        }
        return count;
    }
};

int main()
{
    std::vector<int> nums = {-1, 1, 2, 3, 1};
    int target = 2;
    Solution solu;
    std::cout << solu.countPairs(nums, target) << std::endl;

    return 0;
}

/*
枚举法（暴力嵌套for循环）
T: O(N^2)
S: O(1)
*/