#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int countPairs(std::vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1, count = 0;
        std::sort(nums.begin(), nums.end());
        while (left < right)
        {
            if (nums[left] + nums[right] < target)
            {
                count += right - left;
                left++;
            }
            else
                right--;
        }
        return count;
    }
};

int main()
{
    std::vector<int> nums = {-1, 1, 2, 3, 1};
    int target = 2;
    Solution solu;
    std::cout << solu.countPairs(nums, target) << std::endl;

    return 0;
}

/*
双指针法

先对数组进行排序，从小到大。
左指针指向左边小的，右指针指向右边大的。

nums[left] + nums[right] < target, 则说明nums[right]这个“最右边”的数都不够大，所以从right到left所有的数都是满足的。
下面就可以让left右移，变大一些。

如果是>=target，则说明nums[right]太大了，需要左移减小一下，看看左移后能不能满足< target


T: O(nlogn),主要就是sort排序
S: O(1)
*/