#include <iostream>
#include <vector>
#include <cstdlib>

class Solution
{
public:
    std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> ans = {};
        for (int i = 0; i < nums.size() - 3; i++)
        {
            for (int j = i + 1; j < nums.size() - 2; j++)
            {
                for (int k = j + 1; k < nums.size() - 1; k++)
                {
                    for (int l = k + 1; l < nums.size(); l++)
                    {
                        int sum = nums[i] + nums[j] + nums[k] + nums[l];
                        if (sum == target)
                        {
                            std::vector<int> tmp = {{nums[i], nums[j], nums[k], nums[l]}};
                            ans.push_back(tmp);
                        }
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
枚举法（四层for循环）

T: O(n^4)
S: O(logn) ?? 好像

代码有问题！LeetCode不通过。
没有分析重复的情况。

nums =[2,2,2,2,2]
target = 8
*/