#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int numOfSubarrays(std::vector<int> &arr, int k, int threshold)
    {
        int sum_val = 0, count = 0;
        int sum_threshold = k * threshold;
        for (int i = 0; i < arr.size(); i++)
        {
            sum_val += arr[i];

            if (i < k - 1)
                continue;
            if (sum_val >= sum_threshold)
                count++;
            sum_val -= arr[i - k + 1];
        }
        return count;
    }
};

int main()
{
    std::vector<int> nums = {11, 13, 17, 23, 29, 31, 7, 5, 2, 3};
    int k = 3;
    int td = 5;
    Solution solu;
    std::cout << solu.numOfSubarrays(nums, k, td) << std::endl;

    return 0;
}

/*
定尺寸，滑动窗口
T:O(n)
S:O(1)
*/