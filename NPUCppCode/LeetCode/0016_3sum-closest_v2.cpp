#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

class Solution
{
public:
    int threeSumClosest(std::vector<int> &nums, int target)
    {
        int best_sum = nums[0] + nums[1] + nums[2];
        auto update = [&](int cur_sum)
        {
            best_sum = std::abs(best_sum - target) > std::abs(cur_sum - target) ? cur_sum : best_sum;
        }; // lambda 表达式

        std::sort(nums.begin(), nums.end());

        for (int a = 0; a < nums.size() - 2; a++)
        {
            if (a > 0 && nums[a] == nums[a - 1]) // 处理临近的相同元素
                continue;

            int b = a + 1, c = nums.size() - 1;

            while (b < c)
            {
                int sum = nums[a] + nums[b] + nums[c];
                // std::cout << "Test: " << sum << "=" << nums[a] << "+" << nums[b] << "+" << nums[c] << std::endl;

                if (sum == target) // 最好的情况，和target的差距是0，没啥说的，直接返回就行。
                    return sum;

                update(sum);

                if (sum > target)
                {
                    int c_left = c - 1;
                    while (b < c_left && nums[c_left] == nums[c]) // 处理临近的相同元素
                        c_left--;
                    c = c_left;
                }
                else
                {
                    int b_right = b + 1;
                    while (b_right < c && nums[b_right] == nums[b]) // 处理临近的相同元素
                        b_right++;
                    b = b_right;
                }
            }
        }

        return best_sum;
    }
};

int main()
{
    std::vector<int> nums = {-1, 2, 1, -4};
    int target = 1;
    Solution solu;

    std::cout << solu.threeSumClosest(nums, target) << std::endl;

    return 0;
}

/*
双向指针法

T: O(n^2). O(nlogn)排序的复杂度，还有一个O(N)的for循环，双指针while循环bc，总共时间复杂度看作O(n^2)
S: O(logn). 排序需要使用 O(logN) 的空间
*/