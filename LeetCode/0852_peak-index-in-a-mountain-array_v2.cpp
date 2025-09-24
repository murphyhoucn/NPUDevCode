#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int peakIndexInMountainArray(std::vector<int> &arr)
    {
        int ans = -1;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] > arr[i + 1])
            {
                ans = i;
                break;
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

时间复杂度O(n)
空间复杂度O(1)
*/