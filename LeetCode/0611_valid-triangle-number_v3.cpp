#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int triangleNumber(std::vector<int> &nums)
    {
        int count = 0;
        std::sort(nums.begin(), nums.end());

        for (int c = nums.size() - 1; c > 1; c--) // 从大到小
        {
            if (nums[0] + nums[1] > nums[c]) // 满足这个条件之后，直接break
            {
                count += (c + 1) * c * (c - 1) / 6;
                break;
            }
            if (nums[c - 2] + nums[c - 1] < nums[c])
                continue;

            int b = c - 1;
            int a = 0;

            while (a < b)
            {
                if (nums[a] + nums[b] > nums[c])
                {
                    count += b - a;
                    b--;
                }
                else
                    a++;
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
这个双指针a,b,c的位置跟之前的不一样
双指针的优化
为了能在满足条件的时候直接跳出，c的倒叙的
T: O(n^2)
S: O(1)
*/