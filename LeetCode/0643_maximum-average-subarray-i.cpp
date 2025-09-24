#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    double findMaxAverage(std::vector<int> &nums, int k)
    {
        int sumval = 0;
        double ans = INT32_MIN;

        for (int i = 0; i < nums.size(); i++)
        {
            sumval += nums[i];
            if (i < k - 1)
                continue;

            ans = std::max(ans, static_cast<double>(sumval) / k);

            sumval -= nums[i - k + 1];
        }

        return ans;
    }
};

int main()
{
    std::vector<int> nums = {1, 12, -5, -6, 50, 3};
    int k = 4;
    Solution solu;
    std::cout << solu.findMaxAverage(nums, k) << std::endl;

    return 0;
}

/*
定尺寸，滑动窗口
T:O(n)
S:O(1)
*/