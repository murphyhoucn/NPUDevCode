#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> getAverages(std::vector<int> &nums, int k)
    {
        long long int sum_val = 0;
        int n = nums.size();
        std::vector<int> ans(n, -1);

        for (int i = 0; i < n; i++)
        {
            sum_val += nums[i];
            if (i < 2 * k) // 这里的i是窗口最右边的元素
                continue;
            ans[i - k] = sum_val / (2 * k + 1);

            sum_val -= nums[i - 2 * k];
        }

        return ans;
    }
};

int main()
{
    std::vector<int> nums = {7, 4, 3, 9, 1, 8, 5, 2, 6};
    int k = 3;

    Solution solu;
    std::vector<int> res = solu.getAverages(nums, k);

    for (int i : res)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}

/*
T:O(n)
S:O(n)

题目的描述虽然已知在以圆心为主体，这样在求和的时候不仅要计算圆心之前的还有考虑圆心之后的。
既然窗口尺寸的固定的，那么直接以最右边的边界作为i
因为不满足窗口尺寸2k+1的值都是-1，所以初始化的时候设置为-1，在for循环中，只考虑满足的情况。
*/