#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> shuffle(std::vector<int> &nums, int n)
    {
        std::vector<int> ans(2 * n);
        for (int i = 0; i < n; i++)
        {
            ans[2 * i] = nums[i];
            ans[2 * i + 1] = nums[i + n];
        }

        return ans;
    }
};
int main()
{
    std::vector<int> nums = {2, 5, 1, 3, 4, 7};
    int n = 6;
    Solution solu;

    for (int num : nums)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;

    return 0;
}

/*
T: O(n), for
S: O(n), ans vector
*/