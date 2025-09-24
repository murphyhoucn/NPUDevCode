#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution
{
public:
    long long maxSum(std::vector<int> &nums, int m, int k)
    {
        long long sum_val = 0, ans = 0;
        std::unordered_map<int, int> count;

        for (int i = 0; i < nums.size(); i++)
        {
            sum_val += nums[i];
            count[nums[i]]++;
            if (i < k - 1)
                continue;

            if (count.size() >= m)
                ans = std::max(sum_val, ans);

            int out = nums[i - k + 1];
            sum_val -= out;
            if (--count[out] == 0)
                count.erase(out);
        }
        return ans;
    }
};

int main()
{
    std::vector<int> nums = {2, 6, 7, 3, 1, 7};
    int k = 4; // 定长窗口
    int m = 3;
    Solution solu;
    std::cout << solu.maxSum(nums, m, k) << std::endl;

    return 0;
}

/*
定长窗口滑动
T: O(n)
S: O(k)，hash map size 最大就是窗口长度K
*/