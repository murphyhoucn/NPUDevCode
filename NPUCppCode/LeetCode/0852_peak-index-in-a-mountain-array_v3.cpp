#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int peakIndexInMountainArray(std::vector<int> &arr)
    {
        int ans = -1;

        int left = 1, right = arr.size() - 2;

        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (arr[mid] > arr[mid + 1])
            {
                ans = mid;
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return ans;
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
二分法
时间 O(logn)
空间 O(1)
*/