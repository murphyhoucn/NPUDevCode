#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int triangleNumber(std::vector<int> &nums)
    {
        int count = 0;
        if (nums.size() < 3)
            return 0;

        for (int a = 0; a < nums.size() - 2; a++)
        {
            for (int b = a + 1; b < nums.size() - 1; b++)
            {
                for (int c = b + 1; c < nums.size(); c++)
                {
                    if (nums[a] + nums[b] > nums[c] && nums[a] + nums[c] > nums[b] && nums[b] + nums[c] > nums[a])
                        count++;
                }
            }
        }
        return count;
    }
};

int main()
{
    std::vector<int> nums = {2, 2, 3, 4};

    Solution solu;
    std::cout << solu.triangleNumber(nums) << std::endl;
    return 0;
}

/*
枚举法，暴力嵌套for循环
T: O(n^3)
S: O(1)

超时了！
*/