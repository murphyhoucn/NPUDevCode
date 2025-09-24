#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int peakIndexInMountainArray(std::vector<int> &arr)
    {
        auto max_iter = std::max_element(arr.begin(), arr.end());

        if (max_iter != arr.end())
        {
            return std::distance(arr.begin(), max_iter);
        }
    }
};

int main()
{
    std::vector<int> arr = {0, 10, 5, 2};
    Solution solu;
    std::cout << solu.peakIndexInMountainArray(arr) << std::endl;

    return 0;
}

/*
Leetcode编译出错。
用了API，时间复杂度应该是O(n), 空间复杂度O(1)?
*/