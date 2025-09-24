#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution
{
public:
    long long maximumSubarraySum(std::vector<int> &nums, int k)
    {
        long long sum_val = 0;
        long long ans = 0;
        std::unordered_map<int, int> count;
        for (int i = 0; i < nums.size(); i++)
        {
            sum_val += nums[i];
            count[nums[i]]++;

            if (i < k - 1)
                continue;

            if (count.size() == k)
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
    std::vector<int> nums = {1, 5, 4, 2, 9, 9, 9};
    int k = 3;
    Solution solu;

    std::cout << solu.maximumSubarraySum(nums, k) << std::endl;

    return 0;
}

/*
T:O(n)
S:O(k)，hash map的长度
*/