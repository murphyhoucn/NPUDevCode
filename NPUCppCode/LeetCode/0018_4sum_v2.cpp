#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> ans;

        std::sort(nums.begin(), nums.end());

        for (int a = 0; a < nums.size() - 3; a++)
        {
            if (a > 0 && nums[a] == nums[a - 1])
                continue;
            if ((long)nums[a] + nums[a + 1] + nums[a + 2] + nums[a + 3] > target)
                break;
            if ((long)nums[a] + nums[nums.size() - 3] + nums[nums.size() - 2] + nums[nums.size() - 1] < target)
                continue;

            for (int b = a + 1; b < nums.size() - 2; b++)
            {
                if (b > a + 1 && nums[b] == nums[b - 1])
                    continue;
                if ((long)nums[a] + nums[b] + nums[b + 1] + nums[b + 2] > target)
                    break;
                if ((long)nums[a] + nums[b] + nums[nums.size() - 2] + nums[nums.size() - 1] < target)
                    continue;

                int c = b + 1, d = nums.size() - 1;

                while (c < d)
                {
                    long sum = nums[a] + nums[b] + nums[c] + nums[d];
                    if (sum < target)
                    {
                        c++;
                    }
                    else if (sum > target)
                    {
                        d--;
                    }
                    else
                    {
                        ans.push_back({{nums[a], nums[b], nums[c], nums[d]}});

                        while (c < d && nums[c] == nums[c + 1])
                            c++;
                        c++;

                        while (c < d && nums[d] == nums[d - 1])
                            d--;
                        d--;
                    }
                }
            }
        }

        return ans;
    }
};

int main()
{
    std::vector<int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;
    Solution solu;

    for (auto row : solu.fourSum(nums, target))
    {
        for (int e : row)
        {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

/*
双指针

T: O(n^3)
S: O(logn)

代码有问题！
Leetcode执行出错！

*/