# include<iostream>
# include<vector>

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target)
    {
        std::vector<int> ans;
        for (int i = 0; i < numbers.size(); i++)
        {
            for(int j = i + 1; j < numbers.size(); j++)
            {
                if (numbers[i] + numbers[j] == target)
                {
                    ans = {i + 1, j + 1};
                    return ans;
                }
            }
        }
        return ans;
    }
};

int main()
{
    Solution solu;
    std::vector<int> numbers = {2,7,11,15};
    int target = 9;

    std::vector<int> ans = solu.twoSum(numbers, target);

    std::cout << "ans:" << '[' << ans[0] << ',' << ans[1] << ']' << std::endl;
    return 0;
}


/*
2025.02.20

暴力解法，嵌套两个for循环，时间复杂度O(N^2)。
leetcode提交，结果超时。

numbers是有序数组，这个条件没有用上！
*/