# include<iostream>
# include<vector>

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target)
    {
        std::vector<int> ans;
        int left = 0, right = numbers.size() - 1;
        while (true)
        {
            int sumvalue = numbers[left] + numbers[right];

            if (sumvalue < target){
                left++;
            }
            else if (sumvalue > target)
            {
                right--;
            }
            else
            {
                ans = {left + 1, right + 1};
            }
        }
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

利用数字是从小到大是顺序，把最小的和最大的进行相加，
如果sumvalue < target，说明是最小的“拖累”了sumvalue，左指针右移，使sumvalue变大些；
如果sumvalue > target，说明是最大的“拖累”了sumvalue，右指针左移，使sumvalue变小些；

时间复杂度O(n)
空间复杂度O(1)，只使用了几个额外的变量
*/