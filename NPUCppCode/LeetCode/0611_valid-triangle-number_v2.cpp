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

        for (int c = 2; c < nums.size(); c++)
        {
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
T: O(n^2)
S: O(1)
*/