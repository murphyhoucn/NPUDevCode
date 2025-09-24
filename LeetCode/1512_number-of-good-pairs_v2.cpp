#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int numIdenticalPairs(std::vector<int> &nums)
    {
        std::unordered_map<int, int> hashtable;

        for (int i = 0; i < nums.size(); i++)
        {
            hashtable[nums[i]]++;
        }

        int res = 0;
        for (auto pair : hashtable)
        {
            res += pair.second * (pair.second - 1) / 2;
        }

        return res;
    }
};

int main()
{
    std::vector<int> nums = {1, 2, 3, 1, 1, 3};
    Solution solu;
    std::cout << solu.numIdenticalPairs(nums) << std::endl;

    return 0;
}

/*
暴力统计，嵌套两个for循环
时间复杂度：O(n^2)
空间复杂度：O(1)
*/