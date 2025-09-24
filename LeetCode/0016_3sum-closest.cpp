#include <iostream>
#include <vector>
#include <cstdlib>

class Solution
{
public:
    int threeSumClosest(std::vector<int> &nums, int target)
    {
        int diff = 100000;
        int ans[3] = {0, 0, 0};
        for (int i = 0; i < nums.size() - 2; i++)
        {
            for (int j = i + 1; j < nums.size() - 1; j++)
            {
                for (int k = j + 1; k < nums.size(); k++)
                {
                    int sum = nums[i] + nums[j] + nums[k];
                    if (diff > std::abs(sum - target))
                    {
                        ans[0] = i;
                        ans[1] = j;
                        ans[2] = k;

                        diff = std::abs(sum - target);
                    }
                }
            }
        }
        return nums[ans[0]] + nums[ans[1]] + nums[ans[2]];
    }
};

int main()
{
    std::vector<int> nums = {-1, 2, 1, -4};
    int target = 1;
    Solution solu;

    std::cout << solu.threeSumClosest(nums, target) << std::endl;

    return 0;
}

/*
枚举法（三层for循环）
性能差死了！

T: O(n^3)
S: O(1)
*/